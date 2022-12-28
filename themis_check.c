/*============================[[    beg-code    ]]============================*/
#include    "themis.h"

static int  s_checks    = 0;
static int  s_passed    = 0;
static int  s_updates   = 0;
static int  s_warns     = 0;
static int  s_errors    = 0;

/*
 *  check values (trouble)
 *     £   passed a null
 *     ­   passed a empty string
 *     ?   passed a illegal string
 *     °   in summary, stopped after initial check, trouble with inputs
 *
 *
 *
 *
 */

/*
 * audit...
 *    0 = target name
 *    1 = target exist
 *    2 = target type (dir, reg, ...)
 *    3 = target owner
 *    4 = target group
 *    5 = target perms
 *    6 = source name
 *    7 = source exist (first)
 *    8 = source type (dir, reg, ...)
 *
 * update...
 *   10 = target exist
 *   11 = target type (dir, reg, ...)
 *   12 = target owner
 *   13 = target group
 *   14 = target perms
 *
 *
 *
 *
 */



/*                              0         1         2         3         4         5         6  */
/*                              -123456789-123456789-123456789-123456789-123456789-123456789-1 */
char g_check     [LEN_HUND]  = "·   ······· ·   ·········· ·   ·········· ·   ·········· ·   ·";
char g_fancy     [LEN_RECD]  = "";


/*====================------------------------------------====================*/
/*===----                        small checks                          ----===*/
/*====================------------------------------------====================*/
static void      o___SMALLS__________________o (void) {;}

char         /*--> check a file/dir name -----------------[ leaf   [ ------ ]-*/
CHECK__name             (char a_pos, cchar a_name [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_info    ("g_check"   , g_check);
   --rce;  if (a_pos < 0 || a_pos >= strlen (g_check)) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      g_check [a_pos] = '£';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("a_name"    , a_name);
   l = strlen (a_name);
   DEBUG_PROG   yLOG_value   ("l"         , l);
   --rce;  if (l <= 0) {
      g_check [a_pos] = '­';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check tight)--------------------*/
   DEBUG_PROG   yLOG_note    ("check name quality");
   rc = yVAR_regex ("path_tight", a_name);
   --rce;  if (rc <  0)  {
      /*---(check normal)-------------------*/
      rc = yVAR_regex ("path_norm" , a_name);
      --rce;  if (rc <  0)  {
         DEBUG_PROG   yLOG_note    ("name is not proper");
         g_check [a_pos] = 'F';
         DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_PROG   yLOG_note    ("name follows normal standards");
      g_check [a_pos] = 'n';
   } else {
      DEBUG_PROG   yLOG_note    ("name follows tight standards");
      g_check [a_pos] = 'n';
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> lstat a filesystem entry --------------[ leaf   [ ------ ]-*/
CHECK__exist             (char a_pos, cchar a_name [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   my.exists = '-';
   stat ("/nowheresville", &my.curr_stat);
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_info    ("g_check"   , g_check);
   --rce;  if (a_pos < 0 || a_pos >= strlen (g_check)) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      g_check [a_pos] = '£';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("a_name"    , a_name);
   l = strlen (a_name);
   DEBUG_PROG   yLOG_value   ("l"         , l);
   --rce;  if (l <= 0) {
      g_check [a_pos] = '­';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get attributes)-----------------*/
   rc  = lstat (a_name, &my.curr_stat);
   DEBUG_PROG   yLOG_value   ("lstat"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_note    ("file not found/missing");
      g_check [a_pos] = '-';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(success)------------------------*/
   my.exists = 'y';
   g_check [a_pos] = 'e';
   DEBUG_PROG   yLOG_note    ("success, file found");
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

/*> char         /+--> lstat a filesystem entry --------------[ leaf   [ ------ ]-+/                                                              <* 
 *> CHECK_base         (                                                                                                                          <* 
 *>       char       *a_path,                                                                                                                     <* 
 *>       char       *a_source,                                                                                                                   <* 
 *>       char        a_type,                                                                                                                     <* 
 *>       char        a_mode,                                                                                                                     <* 
 *>       char        a_output )                                                                                                                  <* 
 *> {                                                                                                                                             <* 
 *>    /+---(locals)-----------+-----------+-+/                                                                                                   <* 
 *>    int         rc          = 0;                                                                                                               <* 
 *>    char        rce         = -10;                                                                                                             <* 
 *>    /+---(print header)-------------------+/                                                                                                   <* 
 *>    DEBUG_CONF   yLOG_enter   (__FUNCTION__);                                                                                                  <* 
 *>    fprintf (my.file_full, "      -- %-37.37s : ", a_path);                                                                                    <* 
 *>    /+---(get attributes)-----------------+/                                                                                                   <* 
 *>    g_rcs = 0;                                                                                                                                 <* 
 *>    rc  = lstat (a_path, &my.curr_stat);                                                                                                       <* 
 *>    /+---(handle missing)-----------------+/                                                                                                   <* 
 *>    if (rc < 0) {                                                                                                                              <* 
 *>       g_rcs  = -1;                                                                                                                            <* 
 *>       /+---(audit only)------------------+/                                                                                                   <* 
 *>       --rce;                                                                                                                                  <* 
 *>       FLAG_AUDIT {                                                                                                                            <* 
 *>          RPTG_FULL   fprintf (my.file_full, "WARNING, does not exist (audit only)\n");                                                        <* 
 *>          return rce;                                                                                                                          <* 
 *>       }                                                                                                                                       <* 
 *>       /+---(non-forced)------------------+/                                                                                                   <* 
 *>       --rce;                                                                                                                                  <* 
 *>       if (a_mode != MODE_FORCED) {                                                                                                            <* 
 *>          RPTG_FULL   fprintf (my.file_full, "WARNING, does not exist (non-forced)\n");                                                        <* 
 *>          return rce;                                                                                                                          <* 
 *>       }                                                                                                                                       <* 
 *>       /+---(forced)----------------------+/                                                                                                   <* 
 *>       --rce;                                                                                                                                  <* 
 *>       RPTG_FULL   fprintf (my.file_full, "NOTICE , does not exist (forced)\n");                                                               <* 
 *>       switch (a_type) {                                                                                                                       <* 
 *>       case 'd' :                                                                                                                              <* 
 *>          rc = mkdir   (a_path, 00000   );                                                                                                     <* 
 *>          RPTG_FULL   fprintf (my.file_full, "      -- force-mode, attempt mkdir       (%4d): ", errno);                                       <* 
 *>          break;                                                                                                                               <* 
 *>       case 's' :                                                                                                                              <* 
 *>          rc = symlink (a_source, a_path);                                                                                                     <* 
 *>          RPTG_FULL   fprintf (my.file_full, "      -- force-mode, attempt symlink     (%4d): ", errno);                                       <* 
 *>          break;                                                                                                                               <* 
 *>       default  :                                                                                                                              <* 
 *>          rc = -1;                                                                                                                             <* 
 *>          RPTG_FULL   fprintf (my.file_full, "      -- force-mode but type not forceable     : ");                                             <* 
 *>          break;                                                                                                                               <* 
 *>       }                                                                                                                                       <* 
 *>       if (rc < 0) {                                                                                                                           <* 
 *>          RPTG_FULL   fprintf (my.file_full, "WARNING, could not create\n");                                                                   <* 
 *>          g_rcs = -2;                                                                                                                          <* 
 *>          return rce;                                                                                                                          <* 
 *>       }                                                                                                                                       <* 
 *>       RPTG_FULL   fprintf (my.file_full, "SUCCESS, created\n");                                                                               <* 
 *>       RPTG_FULL   fprintf (my.file_full, "      -- %-37.37s : ", a_path);                                                                     <* 
 *>       rc  = lstat (a_path, &my.curr_stat);                                                                                                    <* 
 *>       if (rc < 0) {                                                                                                                           <* 
 *>          RPTG_FULL   fprintf (my.file_full, "WARNING, still does not exist\n");                                                               <* 
 *>          g_rcs = -3;                                                                                                                          <* 
 *>          return rce - 1;                                                                                                                      <* 
 *>       }                                                                                                                                       <* 
 *>    }                                                                                                                                          <* 
 *>    /+---(success)------------------------+/                                                                                                   <* 
 *>    RPTG_FULL   fprintf (my.file_full, "confirmed\n");                                                                                         <* 
 *>    /+---(check directory)----------------+/                                                                                                   <* 
 *>    rce -= 3;                                                                                                                                  <* 
 *>    if (a_type == 'd') {                                                                                                                       <* 
 *>       RPTG_FULL   fprintf (my.file_full, "      -- expected type is directory       (%02o) : ", (my.curr_stat.st_mode & 0770000) / 010000);   <* 
 *>       if        (S_ISDIR (my.curr_stat.st_mode))  {                                                                                           <* 
 *>          RPTG_FULL   fprintf (my.file_full, "confirmed\n");                                                                                   <* 
*>          return 0;                                                                                                                            <* 
*>       } else if (S_ISLNK (my.curr_stat.st_mode))  {                                                                                           <* 
   *>          RPTG_FULL   fprintf (my.file_full, "WARNING, found symlink\n");                                                                      <* 
      *>          return rce;                                                                                                                          <* 
      *>       } else if (S_ISREG (my.curr_stat.st_mode))  {                                                                                           <* 
         *>          RPTG_FULL   fprintf (my.file_full, "WARNING, found file\n");                                                                         <* 
            *>          return rce - 1;                                                                                                                      <* 
            *>       } else {                                                                                                                                <* 
               *>          RPTG_FULL   fprintf (my.file_full, "WARNING, unknown type\n");                                                                       <* 
                  *>          return rce - 2;                                                                                                                      <* 
                  *>       }                                                                                                                                       <* 
                  *>    }                                                                                                                                          <* 
                  *>    /+---(check symlink)------------------+/                                                                                                   <* 
                  *>    rce -= 3;                                                                                                                                  <* 
                  *>    if (a_type == 's') {                                                                                                                       <* 
                     *>       RPTG_FULL   fprintf (my.file_full, "      -- expected type is symlink         (%02o) : ", (my.curr_stat.st_mode & 0770000) / 010000);   <* 
                        *>       if        (S_ISDIR (my.curr_stat.st_mode))  {                                                                                           <* 
                           *>          RPTG_FULL   fprintf (my.file_full, "WARNING, found directory\n");                                                                    <* 
                              *>          return rce;                                                                                                                          <* 
                              *>       } else if (S_ISLNK (my.curr_stat.st_mode))  {                                                                                           <* 
                                 *>          RPTG_FULL   fprintf (my.file_full, "confirmed\n");                                                                                   <* 
                                    *>          return 0;                                                                                                                            <* 
                                    *>       } else if (S_ISREG (my.curr_stat.st_mode))  {                                                                                           <* 
                                       *>          RPTG_FULL   fprintf (my.file_full, "WARNING, found file\n");                                                                         <* 
                                          *>          return rce - 1;                                                                                                                      <* 
                                          *>       } else {                                                                                                                                <* 
                                             *>          RPTG_FULL   fprintf (my.file_full, "WARNING, unknown type\n");                                                                       <* 
                                                *>          return rce - 2;                                                                                                                      <* 
                                                *>       }                                                                                                                                       <* 
                                                *>    }                                                                                                                                          <* 
                                                *>    /+---(check file)---------------------+/                                                                                                   <* 
                                                *>    rce -= 3;                                                                                                                                  <* 
                                                *>    if (a_type == 'f') {                                                                                                                       <* 
                                                   *>       RPTG_FULL   fprintf (my.file_full, "      -- expected type is regular file    (%02o) : ", (my.curr_stat.st_mode & 0770000) / 010000);   <* 
                                                      *>       if        (S_ISDIR (my.curr_stat.st_mode))  {                                                                                           <* 
                                                         *>          RPTG_FULL   fprintf (my.file_full, "WARNING, found directory\n");                                                                    <* 
                                                            *>          return rce;                                                                                                                          <* 
                                                            *>       } else if (S_ISLNK (my.curr_stat.st_mode))  {                                                                                           <* 
                                                               *>          RPTG_FULL   fprintf (my.file_full, "WARNING, found symlink\n");                                                                      <* 
                                                                  *>          return rce - 1;                                                                                                                      <* 
                                                                  *>       } else if (S_ISREG (my.curr_stat.st_mode))  {                                                                                           <* 
                                                                     *>          RPTG_FULL   fprintf (my.file_full, "confirmed\n");                                                                                   <* 
                                                                        *>          return 0;                                                                                                                            <* 
                                                                        *>       } else {                                                                                                                                <* 
                                                                           *>          RPTG_FULL   fprintf (my.file_full, "WARNING, unknown type\n");                                                                       <* 
                                                                              *>          return rce - 2;                                                                                                                      <* 
                                                                              *>       }                                                                                                                                       <* 
                                                                              *>    }                                                                                                                                          <* 
                                                                              *>    /+---(complete)-----------------------+/                                                                                                   <* 
                                                                              *>    DEBUG_CONF   yLOG_exit    (__FUNCTION__);                                                                                                  <* 
                                                                              *>    return 0;                                                                                                                                  <* 
                                                                              *> }                                                                                                                                             <*/

char         /*--> verify a file -------------------------[ ------ [ ------ ]-*/
CHECK__type             (char a_pos, char a_expect)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   char        x_expect    =  '-';
   char        x_actual    =  '-';
   /*---(print header)-------------------*/
   DEBUG_CONF   yLOG_enter   (__FUNCTION__);
   /*---(expected)------------------------*/
   DEBUG_PROG   yLOG_info    ("g_check"   , g_check);
   --rce;  if (a_pos < 0 || a_pos >= strlen (g_check)) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF   yLOG_char    ("a_expect"  , a_expect);
   for (i = 0; i < MAX_VERB; ++i) {
      if (g_verbs [i].abbr == '-')         break;
      if (a_expect != g_verbs [i].abbr)    continue;
      x_expect = a_expect;
      break;
   }
   DEBUG_CONF   yLOG_char    ("x_expect"  , x_expect);
   --rce;  if (a_expect != x_expect) {
      g_check [a_pos] = '?';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (x_expect == 'f')  x_expect = 'r';
   /*---(missing file)--------------------*/
   --rce;  if (my.exists != 'y') {
      g_check [a_pos] = '-';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(actual)--------------------------*/
   if      (S_ISBLK  (my.curr_stat.st_mode))  x_actual = 'b';
   else if (S_ISCHR  (my.curr_stat.st_mode))  x_actual = 'c';
   else if (S_ISDIR  (my.curr_stat.st_mode))  x_actual = 'd';
   else if (S_ISREG  (my.curr_stat.st_mode))  x_actual = 'r';
   else if (S_ISSOCK (my.curr_stat.st_mode))  x_actual = 'i';
   else if (S_ISFIFO (my.curr_stat.st_mode))  x_actual = 'p';
   else if (S_ISLNK  (my.curr_stat.st_mode))  x_actual = 's';
   else                                       x_actual = '?';
   if (x_actual == 'r') {
      if (my.curr_stat.st_nlink > 1)          x_actual = 'h';
   }
   /*---(check for trouble)--------------*/
   DEBUG_CONF   yLOG_char    ("x_actual"  , x_actual);
   --rce;  if (x_expect != x_actual) {
      g_check [a_pos] = toupper (x_actual);
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   g_check [a_pos] = x_actual;
   /*---(complete)-----------------------*/
   DEBUG_CONF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> verify/change the owner ---------------[ ------ [ ------ ]-*/
CHECK__owner            (char a_pos, cchar a_owner [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   tPASSWD    *p           = NULL;
   int         x_uid       =   -1;
   /*---(print header)-------------------*/
   DEBUG_CONF   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_info    ("g_check"   , g_check);
   --rce;  if (a_pos < 0 || a_pos >= strlen (g_check)) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_point   ("a_owner"   , a_owner);
   --rce;  if (a_owner == NULL) {
      g_check [a_pos] = '£';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("a_owner"   , a_owner);
   l = strlen (a_owner);
   DEBUG_PROG   yLOG_value   ("l"         , l);
   --rce;  if (l <= 0) {
      g_check [a_pos] = '­';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*===[[ NO-TOUCH ]]===================*/
   if (strcmp (a_owner, "tty_root") == 0) {   /* specific to tty devices     */
      g_check [a_pos] = '!';
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(look up owner)------------------*/
   p = getpwnam (a_owner);
   DEBUG_PROG   yLOG_point   ("p"         , p);
   --rce;  if (p == NULL) {
      g_check [a_pos] = '?';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_uid = p->pw_uid;
   DEBUG_PROG   yLOG_value   ("x_uid"     , x_uid);
   /*---(save to global);-----------------*/
   my.e_uid  = x_uid;
   /*---(missing file)--------------------*/
   --rce;  if (my.exists != 'y') {
      g_check [a_pos] = '-';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(look up actual)-----------------*/
   p = getpwuid (my.curr_stat.st_uid);
   DEBUG_PROG   yLOG_point   ("p"         , p);
   --rce;  if (p == NULL) {
      g_check [a_pos] = 'F';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(test match)---------------------*/
   --rce;  if (my.curr_stat.st_uid != x_uid) {
      g_check [a_pos] = '-';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   g_check [a_pos] = 'o';
   /*---(complete)-----------------------*/
   DEBUG_CONF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> verify/change the owner ---------------[ ------ [ ------ ]-*/
CHECK__group            (char a_pos, cchar a_group [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   tGROUP     *g           = NULL;
   int         x_gid       =   -1;
   /*---(print header)-------------------*/
   DEBUG_CONF   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_info    ("g_check"   , g_check);
   --rce;  if (a_pos < 0 || a_pos >= strlen (g_check)) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_point   ("a_group"   , a_group);
   --rce;  if (a_group == NULL) {
      g_check [a_pos] = '£';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("a_group"   , a_group);
   l = strlen (a_group);
   DEBUG_PROG   yLOG_value   ("l"         , l);
   --rce;  if (l <= 0) {
      g_check [a_pos] = '­';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(look up group)------------------*/
   g = getgrnam (a_group);
   DEBUG_PROG   yLOG_point   ("g"         , g);
   --rce;  if (g == NULL) {
      g_check [a_pos] = '?';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_gid = g->gr_gid;
   DEBUG_PROG   yLOG_value   ("x_gid"     , x_gid);
   /*---(save to global);-----------------*/
   my.e_gid  = x_gid;
   /*---(missing file)--------------------*/
   --rce;  if (my.exists != 'y') {
      g_check [a_pos] = '-';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(look up actual)-----------------*/
   g = getgrgid (my.curr_stat.st_gid);
   DEBUG_PROG   yLOG_point   ("g"         , g);
   --rce;  if (g == NULL) {
      g_check [a_pos] = 'F';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(test match)---------------------*/
   --rce;  if (my.curr_stat.st_gid != x_gid) {
      g_check [a_pos] = '-';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   g_check [a_pos] = 'g';
   /*---(complete)-----------------------*/
   DEBUG_CONF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> verify/change the permissions ---------[ ------ [ ------ ]-*/
CHECK__perms            (char a_pos, cchar a_perms [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   int         x_expect    =   -1;
   int         x_actual    =   -1;
   int         i           =    0;
   /*---(print header)-------------------*/
   DEBUG_CONF   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_info    ("g_check"   , g_check);
   --rce;  if (a_pos < 0 || a_pos >= strlen (g_check)) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_point   ("a_perms"   , a_perms);
   --rce;  if (a_perms == NULL) {
      g_check [a_pos] = '£';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("a_perms"   , a_perms);
   l = strlen (a_perms);
   DEBUG_PROG   yLOG_value   ("l"         , l);
   --rce;  if (l <= 0) {
      g_check [a_pos] = '­';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(interpret)----------------------*/
   for (i = 0; i < MAX_PERM; ++i) {
      if (strcmp (g_perms [i].name, "end-of-entries") == 0)  break;
      if (strcmp (g_perms [i].name, a_perms) != 0)           continue;
      x_expect = g_perms [i].value & 007777;
   }
   DEBUG_PROG   yLOG_value   ("x_expect"   , x_expect);
   --rce;  if (x_expect < 0) {
      g_check [a_pos] = '?';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save to global);-----------------*/
   my.e_mode  = x_expect;
   /*---(missing file)--------------------*/
   --rce;  if (my.exists != 'y') {
      g_check [a_pos] = '-';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check match)--------------------*/
   x_actual = my.curr_stat.st_mode & 007777;
   DEBUG_PROG   yLOG_value   ("x_actual"   , x_actual);
   --rce;  if (x_actual != x_expect) {
      g_check [a_pos] = '-';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   my.e_mode       = x_expect;
   g_check [a_pos] = 'p';
   /*---(complete)-----------------------*/
   DEBUG_CONF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
CHECK__link             (char a_pos, char a_chk, cchar a_name [LEN_HUND], cchar a_source [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   char        t           [LEN_HUND]  = "";
   /*---(print header)-------------------*/
   DEBUG_CONF   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_info    ("g_check"   , g_check);
   --rce;  if (a_pos < 0 || a_pos >= strlen (g_check)) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name   == NULL) {
      g_check [a_pos] = '£';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("a_name"    , a_name);
   DEBUG_PROG   yLOG_point   ("a_source"  , a_source);
   --rce;  if (a_source == NULL) {
      g_check [a_pos] = '£';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("a_source"  , a_source);
   /*---(check for missing target)-------*/
   if (g_check [a_chk] == '-') {
      g_check [a_pos] = '-';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check link)---------------------*/
   l  =  readlink (a_name, t, 490);
   DEBUG_PROG   yLOG_value   ("l"         , l);
   --rce;  if (l <= 0) {
      g_check [a_pos] = '!';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   t [l] = '\0';
   DEBUG_PROG   yLOG_info    ("t"         , t);
   /*---(check link)---------------------*/
   --rce;  if (strcmp (t, a_source) != 0) {
      g_check [a_pos] = '-';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   g_check [a_pos] = 'l';
   /*---(complete)-----------------------*/
   DEBUG_CONF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> verify file device numbers ------------[ ------ [ ------ ]-*/
CHECK__nodes            (char a_pos, cchar a_source [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   int         c           =    0;
   char       *p           =    0;
   int         x_emajor, x_eminor;
   int         x_amajor, x_aminor;
   char        x_source    [LEN_HUND] = "";
   char        t           [LEN_HUND] = "";
   /*---(print header)-------------------*/
   DEBUG_CONF   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_info    ("g_check"   , g_check);
   --rce;  if (a_pos < 0 || a_pos >= strlen (g_check)) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_point   ("a_source"  , a_source);
   --rce;  if (a_source == NULL) {
      g_check [a_pos    ] = '£';
      g_check [a_pos + 1] = '£';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("a_source"  , a_source);
   l = strlen (a_source);
   DEBUG_PROG   yLOG_value   ("l"         , l);
   --rce;  if (l <= 0) {
      g_check [a_pos    ] = '­';
      g_check [a_pos + 1] = '­';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (x_source, a_source, LEN_HUND);
   c = strldcnt (a_source, ',', LEN_HUND);
   DEBUG_PROG   yLOG_value   ("c"         , c);
   --rce;  if (c != 1) {
      g_check [a_pos    ] = '?';
      g_check [a_pos + 1] = '?';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(expected major)-----------------*/
   p = strtok (x_source, ",");
   DEBUG_PROG   yLOG_point   ("p"         , p);
   --rce;  if (p == NULL) {
      g_check [a_pos] = '?';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy  (t, p, LEN_HUND);
   strltrim (t, ySTR_BOTH, LEN_HUND);
   DEBUG_PROG   yLOG_info    ("t"         , t);
   x_emajor = atoi (t);
   DEBUG_PROG   yLOG_value   ("x_emajor"  , x_emajor);
   --rce;  if (x_emajor == 0 && strcmp (t, "0") != 0) {
      g_check [a_pos    ] = '?';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(expected minor)-----------------*/
   p = strtok (NULL    , ",");
   DEBUG_PROG   yLOG_point   ("p"         , p);
   --rce;  if (p == NULL) {
      g_check [a_pos + 1] = '?';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy  (t, p, LEN_HUND);
   strltrim (t, ySTR_BOTH, LEN_HUND);
   DEBUG_PROG   yLOG_info    ("t"         , t);
   x_eminor = atoi (t);
   DEBUG_PROG   yLOG_value   ("x_eminor"  , x_eminor);
   --rce;  if (x_emajor == 0 && strcmp (t, "0") != 0) {
      g_check [a_pos + 1] = '?';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save to global);-----------------*/
   my.e_major = x_emajor;
   my.e_minor = x_eminor;
   /*---(missing file)--------------------*/
   --rce;  if (my.exists != 'y') {
      g_check [a_pos] = '-';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(actuals)------------------------*/
   x_amajor = major (my.curr_stat.st_rdev);
   DEBUG_PROG   yLOG_value   ("x_amajor"  , x_amajor);
   if (x_amajor == x_emajor)   g_check [a_pos    ] = 'j';
   else                        g_check [a_pos    ] = '-';
   x_aminor = minor (my.curr_stat.st_rdev);
   DEBUG_PROG   yLOG_value   ("x_aminor"  , x_aminor);
   if (x_aminor == x_eminor)   g_check [a_pos + 1] = 'n';
   else                        g_check [a_pos + 1] = '-';
   /*---(complete)-----------------------*/
   DEBUG_CONF   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       common checks                          ----===*/
/*====================------------------------------------====================*/
static void      o___COMMONS_________________o (void) {;}

char
CHECK_clear             (void)
{
   /*---(initialize)---------------------*/
   /*> s_checks  = a_checks;                                                          <* 
    *> s_passed  = s_updates = s_warns   = s_errors  = 0;                             <*/
   /*---(complete)-----------------------*/
   return 0;
}

/*> char        /+  == 0 (good), < 0 (hard failure), > 0 (unforced change needed) +/                 <* 
 *> CHECK_beginning    (                                                                             <* 
 *>       /+----------+-----------+-----------------------------------------------+/                 <* 
 *>       char       *a_title     ,   /+ title text for reporting                 +/                 <* 
 *>       char       *a_desc      ,   /+ text for report short description        +/                 <* 
 *>       char       *a_path      ,   /+ full path including name                 +/                 <* 
 *>       char        a_mode      )   /+ mode is verify or create/update          +/                 <* 
 *> {  /+---(locals)-----------+-----------+-+/                                                      <* 
 *>    char        rc          = 0;                                                                  <* 
 *>    char        rce         = -10;                                                                <* 
 *>    /+---(header)-------------------------+/                                                      <* 
 *>    DEBUG_PROG   yLOG_enter   (__FUNCTION__);                                                     <* 
 *>    /+---(check name)---------------------+/                                                      <* 
 *>    rc = CHECK__name   ( 0, a_path);                                                              <* 
 *>    --rce; if (rc < 0) {                                                                          <* 
 *>       ++s_errors;                                                                                <* 
 *>       s_warns   += (s_checks - (s_passed + s_updates + s_errors));                               <* 
 *>       RPTG_summ   (s_checks, s_passed, s_updates, s_warns, s_errors);                            <* 
 *>       RPTG_single (my.verb, a_desc, a_mode, s_checks, s_passed, s_updates, s_warns, s_errors);   <* 
 *>       DEBUG_PROG   yLOG_note    ("name not vaiid");                                              <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                             <* 
 *>       return rce;                                                                                <* 
 *>    }                                                                                             <* 
 *>    ++s_passed;  /+ for the naming +/                                                             <* 
 *>    /+---(get attributes)-----------------+/                                                      <* 
 *>    rc = CHECK__exist  (1, a_path);                                                               <* 
 *>    --rce; if (rc < 0) {                                                                          <* 
 *>       ++s_errors;                                                                                <* 
 *>       s_warns   += (s_checks - (s_passed + s_updates + s_errors));                               <* 
 *>       RPTG_summ   (s_checks, s_passed, s_updates, s_warns, s_errors);                            <* 
 *>       RPTG_single (my.verb, a_desc, a_mode, s_checks, s_passed, s_updates, s_warns, s_errors);   <* 
 *>       DEBUG_PROG   yLOG_note    ("path not valid");                                              <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                             <* 
 *>       return rce;                                                                                <* 
 *>    }                                                                                             <* 
 *>    /+---(handle missing)-----------------+/                                                      <* 
 *>    --rce;  if (rc > 0 && a_mode != MODE_FORCED) {                                                <* 
 *>       ++s_errors;                                                                                <* 
 *>       s_warns   += (s_checks - (s_passed + s_updates + s_errors));                               <* 
 *>       RPTG_summ   (s_checks, s_passed, s_updates, s_warns, s_errors);                            <* 
 *>       RPTG_single (my.verb, a_desc, a_mode, s_checks, s_passed, s_updates, s_warns, s_errors);   <* 
 *>       DEBUG_PROG   yLOG_note    ("does not exist, not in forced mode");                          <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                             <* 
 *>       return -(rce);                                                                             <* 
 *>    }                                                                                             <* 
 *>    --rce;  if (rc > 0) {                                                                         <* 
 *>       DEBUG_PROG   yLOG_note    ("does not exist, ready to force");                              <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                             <* 
 *>       return -(rce);                                                                             <* 
 *>    }                                                                                             <* 
 *>    /+---(handle good)--------------------+/                                                      <* 
 *>    DEBUG_PROG   yLOG_note    ("exists and proper");                                              <* 
 *>    ++s_passed;  /+ for the existance +/                                                          <* 
 *>    /+---(complete)-----------------------+/                                                      <* 
 *>    DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                                     <* 
 *>    return 0;                                                                                     <* 
 *> }                                                                                                <*/

/*> char        /+  == 0 (good), < 0 (hard failure), > 0 (unforced change needed) +/                     <* 
 *> CHECK_ending       (                                                                                 <* 
 *>       /+----------+-----------+-----------------------------------------------+/                     <* 
 *>       char        a_abbr      ,   /+ object type abbriviation                 +/                     <* 
 *>       char       *a_path      ,   /+ full path including name                 +/                     <* 
 *>       char       *a_source    ,   /+ link to original file                    +/                     <* 
 *>       char       *a_owner     ,   /+ owner of object                          +/                     <* 
 *>       char       *a_group     ,   /+ group of object                          +/                     <* 
 *>       char       *a_perms     ,   /+ correct permissions                      +/                     <* 
 *>       char        a_mode      )   /+ mode is verify or create/update          +/                     <* 
 *> {  /+---(locals)-----------+-----------+-+/                                                          <* 
 *>    char        rc          = 0;                                                                      <* 
 *>    char        rce         = -10;                                                                    <* 
 *>    /+---(header)-------------------------+/                                                          <* 
 *>    DEBUG_PROG   yLOG_enter   (__FUNCTION__);                                                         <* 
 *>    /+---(check type)---------------------+/                                                          <* 
 *>    if (a_abbr != TYPE_CHAR && a_abbr != TYPE_BLOCK) {                                                <* 
 *>       rc = CHECK__type (2, a_abbr);                                                                  <* 
 *>       --rce;  if (rc < 0) {                                                                          <* 
 *>          ++s_errors;                                                                                 <* 
 *>          s_warns   += (s_checks - (s_passed + s_updates + s_errors));                                <* 
 *>          RPTG_summ   (s_checks, s_passed, s_updates, s_warns, s_errors);                             <* 
 *>          RPTG_single (my.verb, my.desc, a_mode, s_checks, s_passed, s_updates, s_warns, s_errors);   <* 
 *>          DEBUG_PROG   yLOG_note    ("type not valid, no other checks can be made");                  <* 
 *>          DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                              <* 
 *>          return rce;                                                                                 <* 
 *>       }                                                                                              <* 
 *>       ++s_passed;                                                                                    <* 
 *>    }                                                                                                 <* 
 *>    /+---(check link)---------------------+/                                                          <* 
 *>    if (a_abbr == TYPE_SYM) {                                                                         <* 
 *>       rc = SET_link  (a_path, a_source, a_mode);                                                     <* 
 *>       if      (rc < 0)  ++s_errors;                                                                  <* 
 *>       else if (rc > 0)  ++s_updates;                                                                 <* 
 *>       else              ++s_passed;                                                                  <* 
 *>    }                                                                                                 <* 
 *>    /+---(check owner)--------------------+/                                                          <* 
 *>    rc = SET_owner (a_path, a_owner, a_mode);                                                         <* 
 *>    if      (rc < 0)  ++s_errors;                                                                     <* 
 *>    else if (rc > 0)  ++s_updates;                                                                    <* 
 *>    else              ++s_passed;                                                                     <* 
 *>    /+---(check group)--------------------+/                                                          <* 
 *>    rc = SET_group (a_path, a_group, a_mode);                                                         <* 
 *>    if      (rc < 0)  ++s_errors;                                                                     <* 
 *>    else if (rc > 0)  ++s_updates;                                                                    <* 
 *>    else              ++s_passed;                                                                     <* 
 *>    /+---(check permissions)--------------+/                                                          <* 
 *>    if (a_abbr != TYPE_SYM) {                                                                         <* 
 *>       if (a_abbr == TYPE_CHAR && strcmp (a_perms, "tty_tight") == 0) {                               <* 
 *>          rc = SET_perms (a_path, a_abbr, "file_tight", MODE_AUDIT);                                  <* 
 *>          if (rc != 0)  rc = SET_perms (a_path, a_abbr, "dir_tight", a_mode);                         <* 
 *>          if      (rc < 0)  ++s_errors;                                                               <* 
 *>          else if (rc > 0)  ++s_updates;                                                              <* 
 *>          else              ++s_passed;                                                               <* 
 *>       } else {                                                                                       <* 
 *>          rc = SET_perms (a_path, a_abbr, a_perms, a_mode);                                           <* 
 *>          if      (rc < 0)  ++s_errors;                                                               <* 
 *>          else if (rc > 0)  ++s_updates;                                                              <* 
 *>          else              ++s_passed;                                                               <* 
 *>       }                                                                                              <* 
 *>    }                                                                                                 <* 
 *>    /+---(summary)------------------------+/                                                          <* 
 *>    RPTG_summ   (s_checks, s_passed, s_updates, s_warns, s_errors);                                   <* 
 *>    RPTG_single (my.verb, my.desc, a_mode, s_checks, s_passed, s_updates, s_warns, s_errors);         <* 
 *>    /+---(complete)-----------------------+/                                                          <* 
 *>    DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                                         <* 
 *>    return 0;                                                                                         <* 
 *> }                                                                                                    <* 
 *>                                                                                                      <*/


/*====================------------------------------------====================*/
/*===----                         full checks                          ----===*/
/*====================------------------------------------====================*/
static void      o___FULLS___________________o (void) {;}

/*> char                                                                                                                                                      <* 
 *> CHECK_file_NEWER   (char a_abbr, char a_pass, cchar a_name [LEN_HUND], cchar a_owner [LEN_TERSE], cchar a_group [LEN_TERSE], cchar a_perms [LEN_TERSE])   <* 
 *> {                                                                                                                                                         <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                                               <* 
 *>    char        rce         =  -10;                                                                                                                        <* 
 *>    char        rc          =    0;                                                                                                                        <* 
 *>    char        x_pos       =    0;                                                                                                                        <* 
 *>    char        x_twaddle   =  '-';                                                                                                                        <* 
 *>    char        x_save      =  '-';                                                                                                                        <* 
 *>    /+---(print header)-------------------+/                                                                                                               <* 
 *>    DEBUG_CONF   yLOG_enter   (__FUNCTION__);                                                                                                              <* 
 *>    /+---(defense)------------------------+/                                                                                                               <* 
 *>    DEBUG_PROG   yLOG_char    ("a_abbr"    , a_abbr);                                                                                                      <* 
 *>    --rce;  if (a_abbr != TYPE_FILE) {                                                                                                                     <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                                                                      <* 
 *>       return rce;                                                                                                                                         <* 
 *>    }                                                                                                                                                      <* 
 *>    /+---(prepare)------------------------+/                                                                                                               <* 
 *>    DEBUG_CONF   yLOG_value   ("a_pass"    , a_pass);                                                                                                      <* 
 *>    --rce;  switch (a_pass) {                                                                                                                              <* 
 *>    case  1 :  x_pos =  3;  break;                                                                                                                         <* 
 *>    case  2 :  x_pos = 33;  break;                                                                                                                         <* 
 *>    default :                                                                                                                                              <* 
 *>               DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                                                              <* 
 *>               return rce;                                                                                                                                 <* 
 *>               break;                                                                                                                                      <* 
 *>    }                                                                                                                                                      <* 
 *>    /+---(name)---------------------------+/                                                                                                               <* 
 *>    rc = CHECK__name  (++x_pos, a_name);                                                                                                                   <* 
 *>    DEBUG_CONF   yLOG_value   ("name"      , rc);                                                                                                          <* 
 *>    /+---(attributes)---------------------+/                                                                                                               <* 
 *>    if (rc >= 0) {                                                                                                                                         <* 
 *>       rc = CHECK__exist (++x_pos, a_name);                                                                                                                <* 
 *>       DEBUG_CONF   yLOG_value   ("exist"     , rc);                                                                                                       <* 
 *>       rc = CHECK__type  (++x_pos, a_abbr);                                                                                                                <* 
 *>       DEBUG_CONF   yLOG_value   ("type"      , rc);                                                                                                       <* 
 *>       x_save = g_check [x_pos];                                                                                                                           <* 
 *>       rc = CHECK__owner (++x_pos, a_owner);                                                                                                               <* 
 *>       DEBUG_CONF   yLOG_value   ("owner"     , rc);                                                                                                       <* 
 *>       rc = CHECK__group (++x_pos, a_group);                                                                                                               <* 
 *>       DEBUG_CONF   yLOG_value   ("group"     , rc);                                                                                                       <* 
 *>       rc = CHECK__perms (++x_pos, a_perms);                                                                                                               <* 
 *>       DEBUG_CONF   yLOG_value   ("perms"     , rc);                                                                                                       <* 
 *>    } else {                                                                                                                                               <* 
 *>       x_twaddle = 'y';                                                                                                                                    <* 
 *>    }                                                                                                                                                      <* 
 *>    /+---(passing)------------------------+/                                                                                                               <* 
 *>    if (a_pass == 1)  x_pos = 15;                                                                                                                          <* 
 *>    else              x_pos = 45;                                                                                                                          <* 
 *>    if (strncmp (g_check + 4, "terogp····", LEN_TERSE) == 0)  g_check [x_pos] = 'y';                                                                       <* 
 *>    else if (x_twaddle == 'y')                                g_check [x_pos] = 'F';                                                                       <* 
 *>    else if (my.exists != 'y')                                g_check [x_pos] = ' ';                                                                       <* 
 *>    else if (x_save    != 'r')                                g_check [x_pos] = '!';                                                                       <* 
 *>    else                                                      g_check [x_pos] = '-';                                                                       <* 
 *>    /+---(big trouble)--------------------+/                                                                                                               <* 
 *>    --rce;  if (x_twaddle == 'y') {                                                                                                                        <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                                                                      <* 
 *>       return rce;                                                                                                                                         <* 
 *>    }                                                                                                                                                      <* 
 *>    /+---(complete)-----------------------+/                                                                                                               <* 
 *>    DEBUG_CONF   yLOG_exit    (__FUNCTION__);                                                                                                              <* 
 *>    return 0;                                                                                                                                              <* 
 *> }                                                                                                                                                         <*/

char
CHECK__driver      (char a_abbr, char a_pass, cchar a_name [LEN_HUND], cchar a_owner [LEN_TERSE], cchar a_group [LEN_TERSE], cchar a_perms [LEN_TERSE], char a_type, cchar a_source [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_pos       =    0;
   char        x_sum       =    0;
   char        n           =    0;
   char        x_nosource  =  '-';
   char        x_twaddle   =  '-';
   char        x_exist     =  '-';
   char        x_save      =  '-';
   char        x_temp      =  '-';
   char        x_type      =  '-';
   char        x_key       [LEN_LABEL] = "";
   char        x_2nd       [LEN_LABEL] = "";
   char        x_actual    [LEN_LABEL] = "";
   /*---(print header)-------------------*/
   DEBUG_CONF   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   CHECK_clear   ();
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_char    ("a_abbr"    , a_abbr);
   --rce;  if (strchr (g_norms, a_abbr) == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   DEBUG_CONF   yLOG_value   ("a_pass"    , a_pass);
   --rce;  switch (a_pass) {
   case  1 :  x_pos = BEG_CHECK;    x_sum = END_CHECK;    break;
   case  2 :  x_pos = BEG_RECHECK;  x_sum = END_RECHECK;  break;
   default :
              DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
              return rce;
              break;
   }
   n = x_pos;
   /*---(name)---------------------------*/
   rc = CHECK__name  (++n, a_name);
   DEBUG_CONF   yLOG_value   ("name"      , rc);
   /*---(attributes)---------------------*/
   if (rc >= 0) {
      /*---(common)----------------------*/
      rc = CHECK__exist (++n, a_name);
      DEBUG_CONF   yLOG_value   ("exist"     , rc);
      x_exist = g_check [n];
      rc = CHECK__type  (++n, a_abbr);
      DEBUG_CONF   yLOG_value   ("type"      , rc);
      x_save = g_check [n];
      if (x_save == 'r')  x_save = 'f';
      /*---(non-symbolic)----------------*/
      if (a_abbr != 's') {
         rc = CHECK__owner (++n, a_owner);
         DEBUG_CONF   yLOG_value   ("owner"     , rc);
         rc = CHECK__group (++n, a_group);
         DEBUG_CONF   yLOG_value   ("group"     , rc);
         rc = CHECK__perms (++n, a_perms);
         DEBUG_CONF   yLOG_value   ("perms"     , rc);
      }
      /*---(symbolic)-------------------*/
      if (a_abbr == 's') {
         g_check [++n] = '´';
         rc = CHECK__name  (++n, a_source);
         DEBUG_CONF   yLOG_value   ("name"      , rc);
         if (rc >= 0) {
            rc = CHECK__exist (++n, a_source);
            DEBUG_CONF   yLOG_value   ("exist"     , rc);
            if (rc <  0)  x_nosource = 'y';
            rc = CHECK__type  (++n, a_type);
            DEBUG_CONF   yLOG_value   ("type"      , rc);
            x_type = g_check [n];
            rc = CHECK__link  (++n, x_pos + 2, a_name, a_source);
            DEBUG_CONF   yLOG_value   ("link"      , rc);
         } else {
            x_twaddle = 'y';
         }
      }
      /*---(devices)--------------------*/
      if (strchr ("bc", a_abbr) != NULL) {
         g_check [++n] = '´';
         rc = CHECK__nodes (++n, a_source);
         DEBUG_CONF   yLOG_value   ("perms"     , rc);
      }
      /*---(done)-----------------------*/
   } else {
      x_twaddle = 'y';
   }
   /*---(prepare)------------------------*/
   x_temp = a_abbr;
   if (x_temp == 'f')  x_temp = 'r';
   if (a_type == 'f')  a_type = 'r';
   if      (a_abbr == 's') {
      sprintf (x_key, "nes´ne%cl··", a_type);
      sprintf (x_2nd, "n--´ne%c-··", a_type);
   }
   else if (strchr ("bc", a_abbr) != NULL)  sprintf (x_key, "ne%cogp´jn·", x_temp);
   else                                     sprintf (x_key, "ne%cogp····", x_temp);
   DEBUG_CONF   yLOG_info    ("x_key"     , x_key);
   ++x_pos;
   /*---(judge)--------------------------*/
   strlcpy (x_actual, g_check + x_pos, 11);
   if      (strncmp (x_actual, x_key, LEN_TERSE) == 0)  g_check [x_sum] = 'y';
   else if (strncmp (x_actual, x_2nd, LEN_TERSE) == 0)  g_check [x_sum] = ' ';
   else if (strchr  (x_actual, '£') != NULL)            g_check [x_sum] = '°';
   else if (strchr  (x_actual, '­') != NULL)            g_check [x_sum] = '°';
   else if (strchr  (x_actual, '?') != NULL)            g_check [x_sum] = '°';
   else if (x_nosource == 'y')                          g_check [x_sum] = 'F';
   else if (x_twaddle  == 'y')                          g_check [x_sum] = 'f';
   else if (my.exists  != 'y')                          g_check [x_sum] = ' ';
   else if (x_save     != a_abbr)                       g_check [x_sum] = '!';
   else if (a_abbr == 's' && x_type  != a_type)         g_check [x_sum] = '?';
   else                                                 g_check [x_sum] = '-';
   /*---(big trouble)--------------------*/
   --rce;  if (x_twaddle  == 'y') {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_nosource == 'y') {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_CONF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
CHECK_file         (char a_pass, cchar a_name [LEN_HUND], cchar a_owner [LEN_TERSE], cchar a_group [LEN_TERSE], cchar a_perms [LEN_TERSE])
{
   return CHECK__driver (TYPE_FILE , a_pass, a_name, a_owner, a_group, a_perms, '-', "");
}

char
CHECK_dir          (char a_pass, cchar a_name [LEN_HUND], cchar a_owner [LEN_TERSE], cchar a_group [LEN_TERSE], cchar a_perms [LEN_TERSE])
{
   return CHECK__driver (TYPE_DIR  , a_pass, a_name, a_owner, a_group, a_perms, '-', "");
}

char
CHECK_sym          (char a_pass, cchar a_name [LEN_HUND], char a_type, cchar a_source [LEN_HUND])
{
   return CHECK__driver (TYPE_SYM  , a_pass, a_name, "", "", "", a_type, a_source);
}

char
CHECK_char         (char a_pass, cchar a_name [LEN_HUND], cchar a_owner [LEN_TERSE], cchar a_group [LEN_TERSE], cchar a_perms [LEN_TERSE], cchar a_source [LEN_HUND])
{
   return CHECK__driver (TYPE_CHAR , a_pass, a_name, a_owner, a_group, a_perms, '-', a_source);
}

char
CHECK_block        (char a_pass, cchar a_name [LEN_HUND], cchar a_owner [LEN_TERSE], cchar a_group [LEN_TERSE], cchar a_perms [LEN_TERSE], cchar a_source [LEN_HUND])
{
   return CHECK__driver (TYPE_BLOCK, a_pass, a_name, a_owner, a_group, a_perms, '-', a_source);
}

/*> char         /+--> verify a file -------------------------[ ------ [ ------ ]-+/                 <* 
 *> CHECK_file_OLD     (                                                                             <* 
 *>       /+----------+-----------+-----------------------------------------------+/                 <* 
 *>       char       *a_title     ,   /+ text for report title                    +/                 <* 
 *>       char       *a_desc      ,   /+ text for report short description        +/                 <* 
 *>       char        a_abbr      ,   /+ object type abbreviation                 +/                 <* 
 *>       char       *a_path      ,   /+ full path including name                 +/                 <* 
 *>       char       *a_owner     ,   /+ owner of object                          +/                 <* 
 *>       char       *a_group     ,   /+ group of object                          +/                 <* 
 *>       char       *a_perms     ,   /+ correct permissions                      +/                 <* 
 *>       char       *a_source    ,   /+ ((blank))                                +/                 <* 
 *>       char        a_mode      )   /+ mode is verify or create/update          +/                 <* 
 *> {  /+---(locals)-----------+-----------+-+/                                                      <* 
 *>    char        rc          = 0;                                                                  <* 
 *>    char        rce         = -10;                                                                <* 
 *>    char        x_checks    = 6;  /+ name, exist, type, owner, group, perms +/                    <* 
 *>    /+---(header)-------------------------+/                                                      <* 
 *>    DEBUG_PROG   yLOG_enter   (__FUNCTION__);                                                     <* 
 *>    CHECK__clear   (x_checks);                                                                    <* 
 *>    RPTG_subhead (a_title, a_desc, a_mode);                                                       <* 
 *>    /+---(defense)------------------------+/                                                      <* 
 *>    --rce;  if (a_abbr != TYPE_FILE ) {                                                           <* 
 *>       DEBUG_PROG   yLOG_note    ("this function only handles files");                            <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                             <* 
 *>       return rce;                                                                                <* 
 *>    }                                                                                             <* 
 *>    /+---(beginning)----------------------+/                                                      <* 
 *>    rc = CHECK_beginning (a_title, a_desc, a_path, a_mode);                                       <* 
 *>    --rce;  if (rc < 0) {                                                                         <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                             <* 
 *>       return rce;                                                                                <* 
 *>    }                                                                                             <* 
 *>    /+---(forcing)------------------------+/                                                      <* 
 *>    --rce;  if (rc > 0) {                                                                         <* 
 *>       ++s_errors;                                                                                <* 
 *>       s_warns   += (s_checks - (s_passed + s_updates + s_errors));                               <* 
 *>       RPTG_summ   (s_checks, s_passed, s_updates, s_warns, s_errors);                            <* 
 *>       RPTG_single (my.verb, a_desc, a_mode, s_checks, s_passed, s_updates, s_warns, s_errors);   <* 
 *>       DEBUG_PROG   yLOG_note    ("files can not be forced");                                     <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                             <* 
 *>       return rce;                                                                                <* 
 *>    }                                                                                             <* 
 *>    /+---(ending)-------------------------+/                                                      <* 
 *>    rc = CHECK_ending (a_abbr, a_path, a_source, a_owner, a_group, a_perms, a_mode);              <* 
 *>    --rce;  if (rc < 0) {                                                                         <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                             <* 
 *>       return rce;                                                                                <* 
 *>    }                                                                                             <* 
 *>    /+---(complete)-----------------------+/                                                      <* 
 *>    DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                                     <* 
 *>    return 0;                                                                                     <* 
 *> }                                                                                                <*/

/*> char         /+--> verify a file -------------------------[ ------ [ ------ ]-+/                                     <* 
 *> CHECK_sym_OLD      (                                                                                                 <* 
 *>       /+----------+-----------+-----------------------------------------------+/                                     <* 
 *>       char       *a_title     ,   /+ text for report title                    +/                                     <* 
 *>       char       *a_desc      ,   /+ text for report short description        +/                                     <* 
 *>       char        a_abbr      ,   /+ object type abbreviation                 +/                                     <* 
 *>       char       *a_path      ,   /+ full path including name                 +/                                     <* 
 *>       char       *a_owner     ,   /+ owner of object                          +/                                     <* 
 *>       char       *a_group     ,   /+ group of object                          +/                                     <* 
 *>       char       *a_perms     ,   /+ correct permissions                      +/                                     <* 
 *>       char       *a_source    ,   /+ link to original file                    +/                                     <* 
 *>       char        a_mode      )   /+ mode is verify or create/update          +/                                     <* 
 *> {  /+---(locals)-----------+-----------+-+/                                                                          <* 
 *>    char        rc          = 0;                                                                                      <* 
 *>    char        rce         = -10;                                                                                    <* 
 *>    char        x_checks    = 6;  /+ name, exist, type, source, owner, group   +/                                     <* 
 *>    tSTAT       t;                                                                                                    <* 
 *>    /+---(header)-------------------------+/                                                                          <* 
 *>    DEBUG_PROG   yLOG_enter   (__FUNCTION__);                                                                         <* 
 *>    CHECK__clear   (x_checks);                                                                                        <* 
 *>    RPTG_subhead (a_title, a_desc, a_mode);                                                                           <* 
 *>    /+---(defense)------------------------+/                                                                          <* 
 *>    --rce;  if (a_abbr != TYPE_SYM  ) {                                                                               <* 
 *>       DEBUG_PROG   yLOG_note    ("this function only handles symbolic links");                                       <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                                 <* 
 *>       return rce;                                                                                                    <* 
 *>    }                                                                                                                 <* 
 *>    /+---(check source)-------------------+/                                                                          <* 
 *>    --rce;  if (a_source == NULL) {                                                                                   <* 
 *>       RPTG_FULL   fprintf (my.file_full, "      -- TARG1 %-31.31s : FAILURE, can not be null\n", "((null name))");   <* 
 *>       ++s_errors;                                                                                                    <* 
 *>       s_warns   += (s_checks - (s_passed + s_updates + s_errors));                                                   <* 
 *>       RPTG_summ   (s_checks, s_passed, s_updates, s_warns, s_errors);                                                <* 
 *>       RPTG_single (my.verb, a_desc, a_mode, s_checks, s_passed, s_updates, s_warns, s_errors);                       <* 
 *>       return rce;                                                                                                    <* 
 *>    }                                                                                                                 <* 
 *>    RPTG_FULL      fprintf (my.file_full, "      -- TARG1 %-31.31s : source requested\n", a_source);                  <* 
 *>    /+---(check existance)----------------+/                                                                          <* 
 *>    RPTG_FULL      fprintf (my.file_full, "      --       destination      ");                                        <* 
 *>    rc  = lstat (a_source, &t);                                                                                       <* 
 *>    --rce;  if (rc  < 0) {                                                                                            <* 
 *>       RPTG_FULL   fprintf (my.file_full, "   FAILURE     : does not exist\n");                                       <* 
 *>       ++s_errors;                                                                                                    <* 
 *>       s_warns   += (s_checks - (s_passed + s_updates + s_errors));                                                   <* 
 *>       RPTG_summ   (s_checks, s_passed, s_updates, s_warns, s_errors);                                                <* 
 *>       RPTG_single (my.verb, a_desc, a_mode, s_checks, s_passed, s_updates, s_warns, s_errors);                       <* 
 *>       return rce;                                                                                                    <* 
 *>    }                                                                                                                 <* 
 *>    /+---(check type)---------------------+/                                                                          <* 
 *>    if (S_ISDIR (t.st_mode)) {                                                                                        <* 
 *>       RPTG_FULL      fprintf (my.file_full, "   success     : directory exists\n");                                  <* 
 *>    }                                                                                                                 <* 
 *>    else if (S_ISLNK (t.st_mode)) {                                                                                   <* 
 *>       RPTG_FULL      fprintf (my.file_full, "   success     : symlink exists\n");                                    <* 
 *>    }                                                                                                                 <* 
 *>    else if (S_ISREG (t.st_mode)) {                                                                                   <* 
 *>       RPTG_FULL      fprintf (my.file_full, "   success     : reg file exists\n");                                   <* 
 *>    }                                                                                                                 <* 
 *>    else if (S_ISCHR (t.st_mode)) {                                                                                   <* 
 *>       RPTG_FULL      fprintf (my.file_full, "   success     : char device exists\n");                                <* 
 *>    }                                                                                                                 <* 
 *>    else if (S_ISBLK (t.st_mode)) {                                                                                   <* 
 *>       RPTG_FULL      fprintf (my.file_full, "   success     : block device exists\n");                               <* 
 *>    }                                                                                                                 <* 
 *>    else {                                                                                                            <* 
 *>       RPTG_FULL      fprintf (my.file_full, "   success     : fifo/pipe exists\n");                                  <* 
 *>    }                                                                                                                 <* 
 *>    /+---(beginning)----------------------+/                                                                          <* 
 *>    rc = CHECK_beginning (a_title, a_desc, a_path, a_mode);                                                           <* 
 *>    --rce;  if (rc < 0) {                                                                                             <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                                 <* 
*>       return rce;                                                                                                    <* 
*>    }                                                                                                                 <* 
*>    /+---(non-forcing)--------------------+/                                                                          <* 
*>    --rce;  if (rc > 0 && a_mode != MODE_FORCED) {                                                                    <* 
   *>       DEBUG_PROG   yLOG_note    ("not in forced mode");                                                              <* 
      *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                                 <* 
      *>       return -(rce);                                                                                                 <* 
      *>    }                                                                                                                 <* 
      *>    /+---(forced)-------------------------+/                                                                          <* 
      *>    --rce;  if (rc > 0) {                                                                                             <* 
         *>       rc = symlink (a_source, a_path);                                                                               <* 
            *>       RPTG_FULL   fprintf (my.file_full, "      -- TARGT creation         ");                                        <* 
            *>       if (rc != 0) {                                                                                                 <* 
               *>          RPTG_FULL   fprintf (my.file_full, "   FAILURE     : could not force\n");                                   <* 
                  *>          DEBUG_PROG   yLOG_note    ("could not be forced");                                                          <* 
                  *>          DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                              <* 
                  *>          return rce;                                                                                                 <* 
                  *>       }                                                                                                              <* 
                  *>       RPTG_FULL      fprintf (my.file_full, "   success     : file created\n");                                      <* 
                  *>       /+---(re-get stat)-----------------+/                                                                          <* 
                  *>       rc = CHECK__exist (31, a_path);                                                                                <* 
                  *>       --rce; if (rc < 0) {                                                                                           <* 
                     *>          ++s_errors;                                                                                                 <* 
                        *>          s_warns   += (s_checks - (s_passed + s_updates + s_errors));                                                <* 
                        *>          RPTG_summ   (s_checks, s_passed, s_updates, s_warns, s_errors);                                             <* 
                        *>          RPTG_single (my.verb, a_desc, a_mode, s_checks, s_passed, s_updates, s_warns, s_errors);                    <* 
                        *>          DEBUG_PROG   yLOG_note    ("path not valid");                                                               <* 
                        *>          DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                              <* 
                        *>          return rce;                                                                                                 <* 
                        *>       }                                                                                                              <* 
                        *>       /+---(success)---------------------+/                                                                          <* 
                        *>       ++s_updates;                                                                                                   <* 
                        *>    }                                                                                                                 <* 
                        *>    /+---(ending)-------------------------+/                                                                          <* 
                        *>    rc = CHECK_ending (a_abbr, a_path, a_source, a_owner, a_group, a_perms, a_mode);                                  <* 
                        *>    --rce;  if (rc < 0) {                                                                                             <* 
                           *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                                 <* 
                              *>       return rce;                                                                                                    <* 
                              *>    }                                                                                                                 <* 
                              *>    /+---(complete)-----------------------+/                                                                          <* 
                              *>    DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                                                         <* 
                              *>    return 0;                                                                                                         <* 
                              *> }                                                                                                                    <*/

                              /*> char         /+--> verify a directory --------------------[ ------ [ ------ ]-+/                                      <* 
                               *> CHECK_dir_OLD      (                                                                                                  <* 
                               *>       /+----------+-----------+-----------------------------------------------+/                                      <* 
                               *>       char       *a_title     ,   /+ text for report title                    +/                                      <* 
                               *>       char       *a_desc      ,   /+ text for report short description        +/                                      <* 
                               *>       char        a_abbr      ,   /+ object type abbreviation                 +/                                      <* 
                               *>       char       *a_path      ,   /+ full path including name                 +/                                      <* 
                               *>       char       *a_owner     ,   /+ owner of object                          +/                                      <* 
                               *>       char       *a_group     ,   /+ group of object                          +/                                      <* 
                               *>       char       *a_perms     ,   /+ correct permissions                      +/                                      <* 
                               *>       char       *a_source    ,   /+ ((blank))                                +/                                      <* 
                               *>       char        a_mode      )   /+ mode is verify or create/update          +/                                      <* 
                               *> {  /+---(locals)-----------+-----------+-+/                                                                           <* 
                               *>    char        rc          = 0;                                                                                       <* 
                               *>    char        rce         = -10;                                                                                     <* 
                               *>    char        x_checks    = 6;  /+ name, exist, type, owner, group, perms +/                                         <* 
                               *>    char        x_passed    = 0;                                                                                       <* 
                               *>    char        x_updates   = 0;                                                                                       <* 
                               *>    char        x_warns     = 0;                                                                                       <* 
                               *>    char        x_errors    = 0;                                                                                       <* 
                               *>    char        x_temp      [500]       = "";                                                                          <* 
                               *>    /+---(header)-------------------------+/                                                                           <* 
                               *>    DEBUG_PROG   yLOG_enter   (__FUNCTION__);                                                                          <* 
                               *>    CHECK__clear   (x_checks);                                                                                         <* 
                               *>    RPTG_subhead (a_title, a_desc, a_mode);                                                                            <* 
                               *>    /+---(defense)------------------------+/                                                                           <* 
                               *>    --rce;  if (a_abbr != TYPE_DIR  ) {                                                                                <* 
                               *>       DEBUG_PROG   yLOG_note    ("this function only handles directories");                                           <* 
                               *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                                  <* 
                               *>       return rce;                                                                                                     <* 
                               *>    }                                                                                                                  <* 
                               *>    /+---(beginning)----------------------+/                                                                           <* 
                               *>    rc = CHECK_beginning (a_title, a_desc, a_path, a_mode);                                                            <* 
                               *>    --rce;  if (rc < 0) {                                                                                              <* 
                               *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                                  <* 
                               *>       return rce;                                                                                                     <* 
                               *>    }                                                                                                                  <* 
                               *>    /+---(non-forcing)--------------------+/                                                                           <* 
                               *>    --rce;  if (rc > 0 && a_mode != MODE_FORCED) {                                                                     <* 
                               *>       DEBUG_PROG   yLOG_note    ("not in forced mode");                                                               <* 
                               *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                                  <* 
                               *>       return rce;                                                                                                     <* 
                               *>    }                                                                                                                  <* 
                               *>    /+===[[ EXPECT ]]=====================+/                                                                           <* 
                               *>    --rce;  if (a_source == NULL) {                                                                                    <* 
                               *>       RPTG_FULL   fprintf (my.file_full, "      -- %-37.37s : FAILURE, source can not be null\n", "((null name))");   <* 
                               *>       DEBUG_PROG   yLOG_note    ("source is null");                                                                   <* 
                               *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                                  <* 
                               *>       return rce;                                                                                                     <* 
                               *>    }                                                                                                                  <* 
                               *>    /+---(forcing)------------------------+/                                                                           <* 
                               *>    --rce;  if (rc > 0) {                                                                                              <* 
                               *>       rc = mkdir   (a_path, 00000   );                                                                                <* 
                               *>       RPTG_FULL   fprintf (my.file_full, "      -- force-mode, attempt mkdir       (%4d): ", errno);                  <* 
                               *>       if (rc != 0) {                                                                                                  <* 
                               *>          RPTG_FULL   fprintf (my.file_full, "FAILURE, could not force\n");                                            <* 
                               *>          ++s_errors;                                                                                                  <* 
                               *>          s_warns   += (s_checks - (s_passed + s_updates + s_errors));                                                 <* 
                               *>          RPTG_summ   (s_checks, s_passed, s_updates, s_warns, s_errors);                                              <* 
                               *>          RPTG_single (my.verb, a_desc, a_mode, s_checks, s_passed, s_updates, s_warns, s_errors);                     <* 
                               *>          DEBUG_PROG   yLOG_note    ("could not be forced");                                                           <* 
                               *>          DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                               <* 
                               *>          return rce;                                                                                                  <* 
                               *>       }                                                                                                               <* 
                               *>       RPTG_FULL   fprintf (my.file_full, "success, created, done\n");                                                 <* 
                               *>       /+---(re-get stat)-----------------+/                                                                           <* 
                               *>       rc = CHECK__exist (31, a_path);                                                                                 <* 
                               *>       --rce; if (rc < 0) {                                                                                            <* 
                               *>          ++s_errors;                                                                                                  <* 
                               *>          s_warns   += (s_checks - (s_passed + s_updates + s_errors));                                                 <* 
                               *>          RPTG_summ   (s_checks, s_passed, s_updates, s_warns, s_errors);                                              <* 
                              *>          RPTG_single (my.verb, a_desc, a_mode, s_checks, s_passed, s_updates, s_warns, s_errors);                     <* 
                              *>          DEBUG_PROG   yLOG_note    ("path not valid");                                                                <* 
                              *>          DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                               <* 
                              *>          return rce;                                                                                                  <* 
                              *>       }                                                                                                               <* 
                              *>       /+---(success)---------------------+/                                                                           <* 
                              *>       ++s_updates;                                                                                                    <* 
                              *>    }                                                                                                                  <* 
                              *>    /+---(ending)-------------------------+/                                                                           <* 
                              *>    rc = CHECK_ending (a_abbr, a_path, a_source, a_owner, a_group, a_perms, a_mode);                                   <* 
                              *>    --rce;  if (rc < 0) {                                                                                              <* 
                                 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                                  <* 
                                    *>       return rce;                                                                                                     <* 
                                    *>    }                                                                                                                  <* 
                                    *>    /+---(complete)-----------------------+/                                                                           <* 
                                    *>    DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                                                          <* 
                                    *>    return 0;                                                                                                          <* 
                                    *> }                                                                                                                     <*/

                                    /*> char         /+--> verify a directory --------------------[ ------ [ ------ ]-+/                                                  <* 
                                     *> CHECK_device       (                                                                                                              <* 
                                     *>       /+----------+-----------+-----------------------------------------------+/                                                  <* 
                                     *>       char       *a_title     ,   /+ text for report title                    +/                                                  <* 
                                     *>       char       *a_desc      ,   /+ text for report short description        +/                                                  <* 
                                     *>       char        a_abbr      ,   /+ object type abbreviation                 +/                                                  <* 
                                     *>       char       *a_path      ,   /+ full path including name                 +/                                                  <* 
                                     *>       char       *a_owner     ,   /+ owner of object                          +/                                                  <* 
                                     *>       char       *a_group     ,   /+ group of object                          +/                                                  <* 
                                     *>       char       *a_perms     ,   /+ correct permissions                      +/                                                  <* 
                                     *>       char       *a_source    ,   /+ major and minor device numbers           +/                                                  <* 
                                     *>       char        a_mode      )   /+ mode is verify or create/update          +/                                                  <* 
                                     *> {  /+---(locals)-----------+-----------+-+/                                                                                       <* 
                                     *>    char        rc          = 0;                                                                                                   <* 
                                     *>    char        rce         = -10;                                                                                                 <* 
                                     *>    char        x_checks    = 7;  /+ name, exist, type, node, owner, group, perms +/                                               <* 
                                     *>    char        x_temp      [500]       = "";                                                                                      <* 
                                     *>    char       *p           = NULL;                                                                                                <* 
                                     *>    char       *q           = ",";                                                                                                 <* 
                                     *>    char       *r           = NULL;                                                                                                <* 
                                     *>    int         x_major     = 0;                                                                                                   <* 
                                     *>    int         x_minor     = 0;                                                                                                   <* 
                                     *>    /+---(header)-------------------------+/                                                                                       <* 
                                     *>    DEBUG_PROG   yLOG_enter   (__FUNCTION__);                                                                                      <* 
                                     *>    CHECK__clear   (x_checks);                                                                                                     <* 
                                     *>    RPTG_subhead (a_title, a_desc, a_mode);                                                                                        <* 
                                     *>    /+---(defense)------------------------+/                                                                                       <* 
                                     *>    --rce;  if (a_abbr != TYPE_CHAR  && a_abbr != TYPE_BLOCK) {                                                                    <* 
                                     *>       DEBUG_PROG   yLOG_note    ("this function only handles char/block devices");                                                <* 
                                     *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                                              <* 
                                     *>       return rce;                                                                                                                 <* 
                                     *>    }                                                                                                                              <* 
                                     *>    /+---(beginning)----------------------+/                                                                                       <* 
                                     *>    rc = CHECK_beginning (a_title, a_desc, a_path, a_mode);                                                                        <* 
                                     *>    --rce;  if (rc < 0) {                                                                                                          <* 
                                     *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                                              <* 
                                     *>       return rce;                                                                                                                 <* 
                                     *>    }                                                                                                                              <* 
                                     *>    /+---(non-forcing)--------------------+/                                                                                       <* 
                                     *>    --rce;  if (rc > 0 && a_mode != MODE_FORCED) {                                                                                 <* 
                                     *>       DEBUG_PROG   yLOG_note    ("not in forced mode");                                                                           <* 
                                     *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                                              <* 
                                     *>       return -(rce);                                                                                                              <* 
                                     *>    }                                                                                                                              <* 
                                     *>    /+---(check type early )--------------+/                                                                                       <* 
                                     *>    rc = CHECK__type (2, a_abbr);                                                                                                  <* 
                                     *>    --rce;  if (rc < 0) {                                                                                                          <* 
                                     *>       ++s_errors;                                                                                                                 <* 
                                     *>       s_warns   += (s_checks - (s_passed + s_updates + s_errors));                                                                <* 
                                     *>       RPTG_summ   (s_checks, s_passed, s_updates, s_warns, s_errors);                                                             <* 
                                     *>       RPTG_single (my.verb, a_desc, a_mode, s_checks, s_passed, s_updates, s_warns, s_errors);                                    <* 
                                     *>       DEBUG_PROG   yLOG_note    ("type not valid, no other checks can be made");                                                  <* 
                                     *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                                              <* 
                                     *>       return rce;                                                                                                                 <* 
                                     *>    }                                                                                                                              <* 
                                     *>    ++s_passed;                                                                                                                    <* 
                                     *>    /+---(get major, minor)---------------+/                                                                                       <* 
                                     *>    RPTG_FULL   fprintf (my.file_full, "      -- SOURC expect     ");                                                              <* 
                                     *>    /+> RPTG_FULL   fprintf (my.file_full, "ID major ---, minor --- ", x_major, x_minor);   <+/                                    <* 
                                     *>    --rce;  if (a_source == NULL) {                                                                                                <* 
                                     *>       RPTG_FULL   fprintf (my.file_full, "major ---, minor --- :");                                                               <* 
                                     *>       RPTG_FULL   fprintf (my.file_full, "FAILURE, not provided\n");                                                              <* 
                                     *>       ++s_errors;                                                                                                                 <* 
                                     *>       s_warns   += (s_checks - (s_passed + s_updates + s_errors));                                                                <* 
                                     *>       RPTG_summ   (s_checks, s_passed, s_updates, s_warns, s_errors);                                                             <* 
                                     *>       RPTG_single (my.verb, a_desc, a_mode, s_checks, s_passed, s_updates, s_warns, s_errors);                                    <* 
                                     *>       DEBUG_PROG   yLOG_note    ("source was not provided");                                                                      <* 
                                     *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                                              <* 
                                     *>       return rce;                                                                                                                 <* 
                                     *>    }                                                                                                                              <* 
                                     *>    strlcpy (x_temp, a_source, LEN_STR);                                                                                           <* 
                                    *>    p = strtok_r (x_temp, q, &r);                                                                                                  <* 
                                    *>    --rce;  if (p == NULL) {                                                                                                       <* 
                                       *>       RPTG_FULL   fprintf (my.file_full, "major ---, minor --- : ");                                                              <* 
                                          *>       RPTG_FULL   fprintf (my.file_full, "FAILURE, can not read\n");                                                              <* 
                                          *>       ++s_errors;                                                                                                                 <* 
                                          *>       s_warns   += (s_checks - (s_passed + s_updates + s_errors));                                                                <* 
                                          *>       RPTG_summ   (s_checks, s_passed, s_updates, s_warns, s_errors);                                                             <* 
                                          *>       RPTG_single (my.verb, a_desc, a_mode, s_checks, s_passed, s_updates, s_warns, s_errors);                                    <* 
                                          *>       DEBUG_PROG   yLOG_note    ("can not find delimiter in source field");                                                       <* 
                                          *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                                              <* 
                                          *>       return rce;                                                                                                                 <* 
                                          *>    }                                                                                                                              <* 
                                          *>    x_major = atoi (p);                                                                                                            <* 
                                          *>    --rce;  if (x_major <= 0) {                                                                                                    <* 
                                             *>       RPTG_FULL   fprintf (my.file_full, "major ---, minor --- : ");                                                              <* 
                                                *>       RPTG_FULL   fprintf (my.file_full, "FAILURE, major bad\n");                                                                 <* 
                                                *>       ++s_errors;                                                                                                                 <* 
                                                *>       s_warns   += (s_checks - (s_passed + s_updates + s_errors));                                                                <* 
                                                *>       RPTG_summ   (s_checks, s_passed, s_updates, s_warns, s_errors);                                                             <* 
                                                *>       RPTG_single (my.verb, a_desc, a_mode, s_checks, s_passed, s_updates, s_warns, s_errors);                                    <* 
                                                *>       DEBUG_PROG   yLOG_note    ("major device id can not be <= 0");                                                              <* 
                                                *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                                              <* 
                                                *>       return rce;                                                                                                                 <* 
                                                *>    }                                                                                                                              <* 
                                                *>    p = strtok_r (NULL  , q, &r);                                                                                                  <* 
                                                *>    --rce;  if (p == NULL) {                                                                                                       <* 
                                                   *>       RPTG_FULL   fprintf (my.file_full, "major %03d, minor --- : ", x_major);                                                    <* 
                                                      *>       RPTG_FULL   fprintf (my.file_full, "FAILURE, no minor given\n");                                                            <* 
                                                      *>       ++s_errors;                                                                                                                 <* 
                                                      *>       s_warns   += (s_checks - (s_passed + s_updates + s_errors));                                                                <* 
                                                      *>       RPTG_summ   (s_checks, s_passed, s_updates, s_warns, s_errors);                                                             <* 
                                                      *>       RPTG_single (my.verb, a_desc, a_mode, s_checks, s_passed, s_updates, s_warns, s_errors);                                    <* 
                                                      *>       DEBUG_PROG   yLOG_note    ("can not find second field in source field");                                                    <* 
                                                      *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                                              <* 
                                                      *>       return rce;                                                                                                                 <* 
                                                      *>    }                                                                                                                              <* 
                                                      *>    x_minor = atoi (p);                                                                                                            <* 
                                                      *>    --rce;  if (x_minor <= 0) {                                                                                                    <* 
                                                         *>       ySTR_trim  (p, ySTR_BOTH);                                                                                                  <* 
                                                            *>       if (strcmp (p, "0") != 0) {                                                                                                 <* 
                                                               *>          RPTG_FULL   fprintf (my.file_full, "major %03d, minor --- : ", x_major);                                                 <* 
                                                                  *>          RPTG_FULL   fprintf (my.file_full, "FAILURE, minor bad\n");                                                              <* 
                                                                  *>          ++s_errors;                                                                                                              <* 
                                                                  *>          s_warns   += (s_checks - (s_passed + s_updates + s_errors));                                                             <* 
                                                                  *>          RPTG_summ   (s_checks, s_passed, s_updates, s_warns, s_errors);                                                          <* 
                                                                  *>          RPTG_single (my.verb, a_desc, a_mode, s_checks, s_passed, s_updates, s_warns, s_errors);                                 <* 
                                                                  *>          DEBUG_PROG   yLOG_note    ("minor device id can not be <= 0");                                                           <* 
                                                                  *>          DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                                           <* 
                                                                  *>          return rce;                                                                                                              <* 
                                                                  *>       }                                                                                                                           <* 
                                                                  *>    }                                                                                                                              <* 
                                                                  *>    RPTG_FULL   fprintf (my.file_full, "major %03d, minor %03d : ", x_major, x_minor);                                             <* 
                                                                  *>    RPTG_FULL   fprintf (my.file_full, "confirmed (as valid)\n");                                                                  <* 
                                                                  *>    /+---(forcing)------------------------+/                                                                                       <* 
                                                                  *>    --rce;  if (rc > 0) {                                                                                                          <* 
                                                                     *>       if (a_abbr == TYPE_CHAR )  rc = mknod   (a_path, S_IFCHR, makedev (x_major, x_minor));                                      <* 
                                                                        *>       if (a_abbr == TYPE_BLOCK)  rc = mknod   (a_path, S_IFBLK, makedev (x_major, x_minor));                                      <* 
                                                                        *>       RPTG_FULL   fprintf (my.file_full, "      -- force-mode, attempt mknod       (%4d): ", errno);                              <* 
                                                                        *>       if (rc != 0) {                                                                                                              <* 
                                                                           *>          RPTG_FULL   fprintf (my.file_full, "FAILURE, could not force\n");                                                        <* 
                                                                              *>          ++s_errors;                                                                                                              <* 
                                                                              *>          s_warns   += (s_checks - (s_passed + s_updates + s_errors));                                                             <* 
                                                                              *>          RPTG_summ   (s_checks, s_passed, s_updates, s_warns, s_errors);                                                          <* 
                                                                              *>          RPTG_single (my.verb, a_desc, a_mode, s_checks, s_passed, s_updates, s_warns, s_errors);                                 <* 
                                                                              *>          DEBUG_PROG   yLOG_note    ("could not be forced");                                                                       <* 
                                                                              *>          DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                                           <* 
                                                                              *>          return rce;                                                                                                              <* 
                                                                              *>       }                                                                                                                           <* 
                                                                              *>       RPTG_FULL   fprintf (my.file_full, "success, created, done\n");                                                             <* 
                                                                              *>       /+---(re-get stat)-----------------+/                                                                                       <* 
                                                                              *>       rc = CHECK__exist  (31, a_path);                                                                                            <* 
                                                                              *>       --rce; if (rc < 0) {                                                                                                        <* 
                                                                                 *>          ++s_errors;                                                                                                              <* 
                                                                                    *>          s_warns   += (s_checks - (s_passed + s_updates + s_errors));                                                             <* 
                                                                                    *>          RPTG_summ   (s_checks, s_passed, s_updates, s_warns, s_errors);                                                          <* 
                                                                                    *>          RPTG_single (my.verb, a_desc, a_mode, s_checks, s_passed, s_updates, s_warns, s_errors);                                 <* 
                                                                                    *>          DEBUG_PROG   yLOG_note    ("path not valid");                                                                            <* 
                                                                                    *>          DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                                           <* 
                                                                                    *>          return rce;                                                                                                              <* 
                                                                                    *>       }                                                                                                                           <* 
                                                                                    *>       /+---(success)---------------------+/                                                                                       <* 
                                                                                    *>       ++s_updates;                                                                                                                <* 
                                                                                    *>    }                                                                                                                              <* 
                                                                                    *>    /+---(verify major, minor)------------+/                                                                                       <* 
                                                                                    *>    RPTG_FULL   fprintf (my.file_full, "      --       actual     ");                                                              <* 
                                                                                    *>    RPTG_FULL   fprintf (my.file_full, "major %03d, minor %03d : ", major (my.curr_stat.st_rdev), minor (my.curr_stat.st_rdev));   <* 
                                                                                    *>    RPTG_FULL   fprintf (my.file_full, "confirmed (as valid)\n");                                                                  <* 
                                                                                    *>    RPTG_FULL   fprintf (my.file_full, "      --       comparison ");                                                              <* 
                                                                                    *>    --rce;  if (x_major != major (my.curr_stat.st_rdev)) {                                                                         <* 
                                                                                       *>       RPTG_FULL   fprintf (my.file_full, "         FAILURE     : major does not match\n");                                        <* 
                                                                                          *>       ++s_errors;                                                                                                                 <* 
                                                                                          *>       s_warns   += (s_checks - (s_passed + s_updates + s_errors));                                                                <* 
                                                                                          *>       RPTG_summ   (s_checks, s_passed, s_updates, s_warns, s_errors);                                                             <* 
                                                                                          *>       RPTG_single (my.verb, a_desc, a_mode, s_checks, s_passed, s_updates, s_warns, s_errors);                                    <* 
                                                                                          *>       DEBUG_PROG   yLOG_note    ("major device id does not match");                                                               <* 
                                                                                          *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                                              <* 
                                                                                          *>       return rce;                                                                                                                 <* 
                                                                                          *>    }                                                                                                                              <* 
                                                                                          *>    --rce;  if (x_minor != minor (my.curr_stat.st_rdev)) {                                                                         <* 
                                                                                             *>       RPTG_FULL   fprintf (my.file_full, "         FAILURE     : minor does not match\n");                                        <* 
                                                                                                *>       ++s_errors;                                                                                                                 <* 
                                                                                                *>       s_warns   += (s_checks - (s_passed + s_updates + s_errors));                                                                <* 
                                                                                                *>       RPTG_summ   (s_checks, s_passed, s_updates, s_warns, s_errors);                                                             <* 
                                                                                                *>       RPTG_single (my.verb, a_desc, a_mode, s_checks, s_passed, s_updates, s_warns, s_errors);                                    <* 
                                                                                                *>       DEBUG_PROG   yLOG_note    ("minor device id does not match");                                                               <* 
                                                                                                *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                                              <* 
                                                                                                *>       return rce;                                                                                                                 <* 
                                                                                                *>    }                                                                                                                              <* 
                                                                                                *>    RPTG_FULL   fprintf (my.file_full, "         success     : exact match, done\n");                                              <* 
                                                                                                *>    ++s_passed;                                                                                                                    <* 
                                                                                                *>    /+---(ending)-------------------------+/                                                                                       <* 
                                                                                                *>    rc = CHECK_ending (a_abbr, a_path, a_source, a_owner, a_group, a_perms, a_mode);                                               <* 
                                                                                                *>    --rce;  if (rc < 0) {                                                                                                          <* 
                                                                                                   *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                                              <* 
                                                                                                      *>       return rce;                                                                                                                 <* 
                                                                                                      *>    }                                                                                                                              <* 
                                                                                                      *>    /+---(complete)-----------------------+/                                                                                       <* 
                                                                                                      *>    DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                                                                      <* 
                                                                                                      *>    return 0;                                                                                                                      <* 
                                                                                                      *> }                                                                                                                                 <*/



                                                                                                      /*====================------------------------------------====================*/
                                                                                                      /*===----                    unit testing accessor                     ----===*/
                                                                                                      /*====================------------------------------------====================*/
                                                                                                      static void      o___UNITTEST________________o (void) {;}

char*            /* [------] unit test accessor ------------------------------*/
CHECK__unit             (char *a_question, int a_num)
{
   /*---(prepare)------------------------*/
   strlcpy  (unit_answer, "CONF_unit        : question not understood", LEN_UNIT);
   /*---(fields)-------------------------*/
   if      (strncmp (a_question, "check"          , 20)   == 0) {
      snprintf (unit_answer, LEN_UNIT, "CHECK check      : å%sæ", g_check);
   }
   else if (strncmp (a_question, "stats"          , 20)   == 0) {
      snprintf (unit_answer, LEN_UNIT, "CHECK_stats      : c (%2d), p (%2d), u (%2d), w (%2d), e (%2d)", s_checks, s_passed, s_updates, s_warns, s_errors);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}
