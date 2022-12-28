/*============================[[    beg-code    ]]============================*/
#include    "themis.h"


/*---(unit testing saved fields)---------*/
char        u_aowner     [LEN_NAME] = "";
char        u_agroup     [LEN_NAME] = "";
char        u_aperms     [LEN_NAME] = "";
char        u_eowner     [LEN_NAME] = "";
char        u_egroup     [LEN_NAME] = "";
char        u_eperms     [LEN_NAME] = "";

char        g_permtext [10][5] = {
   "---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"
};

char        g_modetext [10][5] = {
   "---", "--s", "-g-", "-gs", "u--", "u-s", "ug-", "ugs"
};

const tPERM g_perms [MAX_PERM] = {
   /* 123456789012345    12345678901234567890123456789012345678901234567890123456789012345678901234567890   12345 */
   /* ---name--------    ---description------------------------------------------------------------------   perms */
   { "g_only"         , "only the group can see, access, or modify"                                       , 00070 },
   { "g_share"        , "only the group can modify, but all others can see and access"                    , 00075 },
   { "f_nodel"        , "everyone can see, access, and modify, but only owner can delete"                 , 01777 },
   /*---(directories)-------------*/
   { "d_open"         , "everyone can access directory, then list, read, create, and delete files"        , 00777 },
   { "d_control"      , "owner and group can do anything, everyone else can do nothing"                   , 00770 },
   { "d_normal"       , "everyone can access directory, group and other can list and read files only"     , 00755 },
   { "d_secure"       , "owner can do anything,  group can list and read files only, all others nothing"  , 00750 },
   { "d_tight"        , "owner can do anything, all others nothing"                                       , 00700 },
   { "r_share"        , "only root specifically can modify; but all others can see and access"            , 00555 },
   { "r_only"         , "only root specifically can sse, access, or modify; even root group can not"      , 00000 },
   /*---(regular files)-----------*/
   { "f_open"         , "everyone can read and write"                                                     , 00666 },
   { "f_control"      , "owner and group can read and write, everyone else gets nothing"                  , 00660 },
   { "f_normal"       , "owner can read and write, everyone else can read only"                           , 00644 },
   { "f_secure"       , "owner can read and write, group can read only, everyone else gets nothing"       , 00640 },
   { "f_tight"        , "owner can read and write, everyone else gets nothing"                            , 00600 },
   /*---(end)---------------------*/
   { "end-of-entries" , "---marker---"                                                                    , 00000 },
};





typedef     struct tm    tTIME;

typedef     struct stat  tSTAT;
tSTAT       s;
char        g_rcs       = 0;

#define     MAX_STR     500


char
SET__exist         (char a_pos, char a_chk)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_name      =  '·';
   char        x_chk       =  '·';
   /*---(print header)-------------------*/
   DEBUG_CONF   yLOG_enter   (__FUNCTION__);
   /*---(quick-out)----------------------*/
   DEBUG_PROG   yLOG_char    ("my.act"    , my.act);
   --rce;  if (my.act != 'a') {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_info    ("g_check"   , g_check);
   DEBUG_PROG   yLOG_value   ("a_pos"     , a_pos);
   --rce;  if (a_pos < 0 || a_pos >= strlen (g_check)) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_value   ("a_chk"     , a_chk);
   --rce;  if (a_chk < 0 || a_chk >= strlen (g_check)) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_name = g_check [a_chk - 1];
   DEBUG_PROG   yLOG_char    ("x_name"    , x_name);
   --rce;  switch (x_name) {
   case 'n'  :
      DEBUG_PROG   yLOG_note    ("name is good");
      break;
   default   :
      DEBUG_PROG   yLOG_note    ("name is illegal");
      g_check [a_pos] = '°';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
      break;
   }
   x_chk = g_check [a_chk];
   DEBUG_PROG   yLOG_char    ("x_chk"     , x_chk);
   --rce;  switch (x_chk) {
   case '-'  :
      DEBUG_PROG   yLOG_note    ("needs to be created");
      break;
   case 'e'  :
      DEBUG_PROG   yLOG_note    ("nothing to do");
      g_check [a_pos] = 'e';
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return 0;
      break;
   case '·'  :
      DEBUG_PROG   yLOG_note    ("pre-check was never run");
      g_check [a_pos] = '?';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
      break;
   default   :
      DEBUG_PROG   yLOG_note    ("wrong type, not fixable");
      g_check [a_pos] = '°';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
      break;
   }
   /*---(make update)--------------------*/
   DEBUG_PROG   yLOG_char    ("my.abbr"   , my.abbr);
   --rce;  switch (my.abbr) {
   case TYPE_BLOCK : 
      rc = mknod   (my.target, S_IFBLK, makedev (my.e_major, my.e_minor));
      DEBUG_PROG   yLOG_value   ("block"     , rc);
      break;
   case TYPE_CHAR  : 
      rc = mknod   (my.target, S_IFCHR, makedev (my.e_major, my.e_minor));
      DEBUG_PROG   yLOG_value   ("char"      , rc);
      break;
   case TYPE_DIR   : 
      rc = mkdir   (my.target, 00000);
      DEBUG_PROG   yLOG_value   ("dir"       , rc);
      break;
   case TYPE_FILE  : 
      DEBUG_PROG   yLOG_note    ("files will not be made, adminstrator must move");
      break;
   case TYPE_HARD  : 
      DEBUG_PROG   yLOG_note    ("hard, TBD");
      /*   rc = link (new, old);   */
      break;
   case TYPE_IPSOC : 
      DEBUG_PROG   yLOG_note    ("ipsoc, TBD");
      break;
   case TYPE_PIPE  : 
      DEBUG_PROG   yLOG_note    ("pipe, TBD");
      break;
   case TYPE_SYM   : 
      DEBUG_PROG   yLOG_info    ("my.source" , my.source);
      DEBUG_PROG   yLOG_info    ("my.target" , my.target);
      rc = symlink (my.source, my.target);
      DEBUG_PROG   yLOG_value   ("sym"       , rc);
      break;
   default         :
      DEBUG_PROG   yLOG_note    ("do not understand type");
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
      break;
   }
   /*---(save-back)----------------------*/
   --rce;  if (rc < 0) {
      g_check [a_pos] = '°';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   g_check [a_pos] = toupper (my.abbr);
   /*---(complete)-----------------------*/
   DEBUG_CONF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> verify/change the owner ---------------[ ------ [ ------ ]-*/
SET__owner         (char a_pos, char a_chk)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_chk       =  '·';
   /*---(print header)-------------------*/
   DEBUG_CONF   yLOG_enter   (__FUNCTION__);
   /*---(quick-out)----------------------*/
   DEBUG_PROG   yLOG_char    ("my.act"    , my.act);
   --rce;  if (my.act != 'a') {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_info    ("g_check"   , g_check);
   DEBUG_PROG   yLOG_value   ("a_pos"     , a_pos);
   --rce;  if (a_pos < 0 || a_pos >= strlen (g_check)) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_value   ("a_chk"     , a_chk);
   --rce;  if (a_chk < 0 || a_chk >= strlen (g_check)) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_chk = g_check [a_chk];
   DEBUG_PROG   yLOG_char    ("x_chk"     , x_chk);
   --rce;  switch (x_chk) {
   case '-'  :
      DEBUG_PROG   yLOG_note    ("fixable");
      break;
   case 'o'  :
      DEBUG_PROG   yLOG_note    ("nothing to do");
      g_check [a_pos] = 'o';
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return 0;
      break;
   case '·'  :
      DEBUG_PROG   yLOG_note    ("pre-check was never run");
      g_check [a_pos] = '?';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
      break;
   default   :
      DEBUG_PROG   yLOG_note    ("not fixable");
      g_check [a_pos] = '°';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
      break;
   }
   DEBUG_PROG   yLOG_value   ("my.e_uid"  , my.e_uid);
   --rce;  if (my.e_uid < 0) {
      g_check [a_pos] = '?';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(make update)--------------------*/
   rc  = lchown (my.target, my.e_uid, -1);
   DEBUG_PROG   yLOG_value   ("lchown"    , rc);
   --rce;  if (rc < 0) {
      g_check [a_pos] = '!';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   g_check [a_pos] = 'O';
   /*---(complete)-----------------------*/
   DEBUG_CONF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> verify/change the owner ---------------[ ------ [ ------ ]-*/
SET__group         (char a_pos, char a_chk)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_chk       =  '·';
   /*---(print header)-------------------*/
   DEBUG_CONF   yLOG_enter   (__FUNCTION__);
   /*---(quick-out)----------------------*/
   DEBUG_PROG   yLOG_char    ("my.act"    , my.act);
   --rce;  if (my.act != 'a') {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_info    ("g_check"   , g_check);
   DEBUG_PROG   yLOG_value   ("a_pos"     , a_pos);
   --rce;  if (a_pos < 0 || a_pos >= strlen (g_check)) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_value   ("a_chk"     , a_chk);
   --rce;  if (a_chk < 0 || a_chk >= strlen (g_check)) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_chk = g_check [a_chk];
   DEBUG_PROG   yLOG_char    ("x_chk"     , x_chk);
   --rce;  switch (x_chk) {
   case '-'  :
      DEBUG_PROG   yLOG_note    ("fixable");
      break;
   case 'g'  :
      DEBUG_PROG   yLOG_note    ("nothing to do");
      g_check [a_pos] = 'g';
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return 0;
      break;
   case '·'  :
      DEBUG_PROG   yLOG_note    ("pre-check was never run");
      g_check [a_pos] = '?';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
      break;
   default   :
      DEBUG_PROG   yLOG_note    ("not fixable");
      g_check [a_pos] = '°';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
      break;
   }
   DEBUG_PROG   yLOG_value   ("my.e_gid"  , my.e_gid);
   --rce;  if (my.e_gid < 0) {
      g_check [a_pos] = '?';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(make update)--------------------*/
   rc  = lchown (my.target, -1, my.e_gid);
   DEBUG_PROG   yLOG_value   ("lchown"    , rc);
   --rce;  if (rc < 0) {
      g_check [a_pos] = '!';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   g_check [a_pos] = 'G';
   /*---(complete)-----------------------*/
   DEBUG_CONF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> verify/change the owner ---------------[ ------ [ ------ ]-*/
SET__perms         (char a_pos, char a_chk)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_chk       =  '·';
   /*---(print header)-------------------*/
   DEBUG_CONF   yLOG_enter   (__FUNCTION__);
   /*---(quick-out)----------------------*/
   DEBUG_PROG   yLOG_char    ("my.act"    , my.act);
   --rce;  if (my.act != 'a') {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_info    ("g_check"   , g_check);
   DEBUG_PROG   yLOG_value   ("a_pos"     , a_pos);
   --rce;  if (a_pos < 0 || a_pos >= strlen (g_check)) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_value   ("a_chk"     , a_chk);
   --rce;  if (a_chk < 0 || a_chk >= strlen (g_check)) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_chk = g_check [a_chk];
   DEBUG_PROG   yLOG_char    ("x_chk"     , x_chk);
   --rce;  switch (x_chk) {
   case '-'  :
      DEBUG_PROG   yLOG_note    ("fixable");
      break;
   case 'p'  :
      DEBUG_PROG   yLOG_note    ("nothing to do");
      g_check [a_pos] = 'p';
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return 0;
      break;
   case '·'  :
      DEBUG_PROG   yLOG_note    ("pre-check was never run");
      g_check [a_pos] = '?';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
      break;
   default   :
      DEBUG_PROG   yLOG_note    ("not fixable");
      g_check [a_pos] = '°';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
      break;
   }
   DEBUG_PROG   yLOG_value   ("my.e_mode"  , my.e_mode);
   --rce;  if (my.e_mode < 0) {
      g_check [a_pos] = '?';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(make update)--------------------*/
   rc  = chmod (my.target, my.e_mode);
   DEBUG_PROG   yLOG_value   ("chmod"     , rc);
   --rce;  if (rc < 0) {
      g_check [a_pos] = '!';
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   g_check [a_pos] = 'P';
   /*---(complete)-----------------------*/
   DEBUG_CONF   yLOG_exit    (__FUNCTION__);
   return 0;
}







/*====================------------------------------------====================*/
/*===----                            utilities                         ----===*/
/*====================------------------------------------====================*/
static void  o___UTILITIES_______o () { return; }

char        s_string    [MAX_STR];

char*        /*--> clean whitespace from a string --------[--------[--------]-*/
ySTR_trim          (char *a_source, char a_mode)
{
   /*---(design notes)-------------------*/
   /*
    *   n = none   (string untouched)
    *   h = head   (all leading spaces gone)
    *   t = tail   (all ending spaces gone)
    *   b = both   (head and tail)
    *   s = single (both plus internal not-in-strings compressed to one space)
    *   e = every  (both plus internal not-in-strings taken out)
    *   m = max    (both plus all internal taken fully out)
    *
    */
   /*---(locals)-----------+-----------+-*/
   int         i, j;                             /* iterators -- characters   */
   int         x_len       = 0;                  /* source string length      */
   int         x_count     = 0;                  /* whitespace counter        */
   int         x_limit     = 0;
   char        in_str      = '-';
   /*---(defense: bad source)------------*/
   strcpy (s_string, "(null)");
   if (a_source == NULL)   return NULL;
   x_len = strlen(a_source);
   strcpy (s_string, "(empty)");
   if (x_len    <= 0   )   return NULL;
   /*---(prepare)------------------------*/
   if (a_mode == 's')   x_limit = 1;
   /*---(leading whitespace)-------------*/
   if (strchr("hbsem", a_mode) != 0) {
      for (i = 0; i <= x_len; ++i) {
         if (a_source[0] != ' ') break;
         for (j = 0; j <= x_len; ++j)
            a_source[j] = a_source[j + 1];
         --x_len;
      }
   }
   /*---(trailing whitespace)------------*/
   if (strchr("tbsem", a_mode) != 0) {
      for (i = x_len - 1; i >= 0; --i) {
         if (a_source[i] != ' ') break;
         a_source[i] = '\0';
         --x_len;
      }
   }
   /*---(internal whitespace)------------*/
   if (strchr("esm" , a_mode) != 0) {
      for (i = 0; i <= x_len; ++i) {
         /*---(check for strings)--------*/
         if (a_mode != 'm') {
            if (in_str == 'y') {
               if (a_source[i] == '"') {
                  /*> if (i > 0 && a_source[i-1] == '\\')  continue;                  <*/
                  in_str = '-';
                  continue;
               }
               continue;
            } else {
               if (a_source[i] == '"') {
                  /*> if (i > 0 && a_source[i-1] == '\\')  continue;                  <*/
                  in_str = 'y';
                  continue;
               }
            }
         }
         /*---(check limit)--------------*/
         if (a_source[i] != ' '    )  { x_count = 0; continue; }
         if (x_count   <  x_limit)  { ++x_count;   continue; }
         /*---(compress)-----------------*/
         for (j = i; j <= x_len; ++j)
            a_source[j] = a_source[j + 1];
         --x_len;
         --i;
         /*---(done)---------------------*/
      }
   }
   /*---(prepare for return)-------------*/
   strncpy (s_string, a_source, MAX_STR);
   /*---(complete)-----------------------*/
   return a_source;
}

char         /*--> get a filesystem symlink name ---------[ ------ [ ------ ]-*/
SET_link           (
      char       *a_path,
      char       *a_source,
      char        a_mode)
{  /*---(design notes)-------------------*/
   /*
    * return   : 0 good, no changes; < 0 failed; > 0  update needed/done
    * mode     : audit just checks, all others can replace
    * previous : file and source checked/exists/created
    *
    */
   /*---(locals)-----------+-----------+-*/
   int         rc          =   0;
   char        rce         = -10;
   int         x_len       =   0;
   char        x_temp      [500]       = "";
   tSTAT       t;
   /*---(defenses)-----------------------*/
   --rce;  if (a_path   == NULL) {
      return rce;
   }
   --rce;  if (a_source == NULL) {
      return rce;
   }
   /*---(check link)---------------------*/
   x_len  =  readlink (a_path, x_temp, 490);
   --rce;  if (x_len >= 0) {
      x_temp [x_len] = '\0';
      RPTG_FULL      fprintf (my.file_full, "      -- TARG2 %-31.31s : current actual\n", x_temp);
      /*---(test match)---------------------*/
      --rce;  if (strcmp (a_source, x_temp) == 0) {
         RPTG_FULL   fprintf (my.file_full, "      --       comparison       ");
         RPTG_FULL   fprintf (my.file_full, "   success     : exact match, done\n");
         return 0;
      }
   } else {
      RPTG_FULL   fprintf (my.file_full, "      -- TARG2 %-31.31s : current actual\n", "((null))");
   }
   /*---(check unforced miss)------------*/
   RPTG_FULL   fprintf (my.file_full, "      --       comparison       ");
   --rce;  if (a_mode != MODE_HAMMER && a_mode != MODE_FORCED && a_mode != MODE_UPDATE) {
      RPTG_FULL   fprintf (my.file_full, "   WARNING     : does not match (no force)\n");
      return rce;
   }
   /*---(attempt force)------------------*/
   RPTG_FULL      fprintf (my.file_full, "   UPDATE REQD : forced mode\n");
   /*---(handle missing)-----------------*/
   RPTG_FULL      fprintf (my.file_full, "      --       updating         ");
   rc = remove (a_path);
   if (rc < 0) {
      RPTG_FULL   fprintf (my.file_full, "   FAILURE     : could not remove existing\n");
      return rce;
   }
   rc = symlink (a_source, a_path);
   if (rc < 0) {
      RPTG_FULL   fprintf (my.file_full, "   FAILURE     : could not replace with new\n");
      return rce;
   }
   RPTG_FULL   fprintf (my.file_full, "   success     : removed and re-added\n");
   /*---(reaquire the object)------------*/
   rc = CHECK__exist (31, a_path);
   --rce;  if (rc < 0) {
      return rce;
   }
   /*---(check the link)-----------------*/
   x_len  =  readlink (a_path, x_temp, 490);
   --rce;  if (x_len >= 0) {
      x_temp [x_len] = '\0';
      RPTG_FULL      fprintf (my.file_full, "      --       %-31.31s : new actual\n", x_temp);
      RPTG_FULL   fprintf (my.file_full, "      --       comparison       ");
      if (strcmp (a_source, x_temp) == 0) {
         RPTG_FULL   fprintf (my.file_full, "   success     : exact match, done\n");
         return -(rce);
      }
      RPTG_FULL   fprintf (my.file_full, "   FAILURE     : still not match\n");
      return rce;
   }
   RPTG_FULL   fprintf (my.file_full, "   FAILURE     : can not read link\n");
   /*---(complete)-----------------------*/
   --rce;
   return rce;
}

char         /*--> verify/change the owner ---------------[ ------ [ ------ ]-*/
SET_owner          (
      char       *a_path,     /* full path including name                     */
      char       *a_owner,    /* owner of filesystem object                   */
      char        a_mode)     /* mode is verify or create/update              */
{  /*---(locals)-----------+-----------+-*/
   tPASSWD    *p           = NULL;
   char        rc          = 0;
   char        rce         = -10;
   int         x_uid       = -1;
   /*---(defenses)-----------------------*/
   --rce;  if (a_path  == NULL) {
      return rce;
   }
   /*---(prepare)------------------------*/
   strlcpy (u_aowner, "---(NF)---", LEN_NAME);
   strlcpy (u_eowner, "---(NF)---", LEN_NAME);
   /*===[[ ACTUAL ]]=====================*/
   RPTG_FULL      fprintf (my.file_full, "      -- OWNER actual           ");
   /*---(look up actual)-----------------*/
   p = getpwuid (my.curr_stat.st_uid);
   --rce;  if (p == NULL) {
      RPTG_FULL   fprintf (my.file_full, "%4d %-9.9s : FAILED, invalid\n"    , my.curr_stat.st_uid, "(null)---");
      return rce;
   }
   RPTG_FULL      fprintf (my.file_full, "%4d %-9.9s : confirmed (as valid)\n", my.curr_stat.st_uid, p->pw_name);
   strlcpy (u_aowner, p->pw_name, LEN_NAME);
   /*===[[ EXPECT ]]=====================*/
   RPTG_FULL      fprintf (my.file_full, "      --       expected         ");
   /*---(defenses)-----------------------*/
   --rce;  if (a_owner == NULL) {
      RPTG_FULL   fprintf (my.file_full, "   - %-9.9s : FAILED, null\n"      , "(null)---");
      return rce;
   }
   strlcpy (u_eowner, a_owner, LEN_NAME);
   /*===[[ NO-TOUCH ]]===================*/
   if (strcmp (a_owner, "tty_root") == 0) {   /* specific to tty devices     */
      RPTG_FULL   fprintf (my.file_full, "%4d %-9.9s : confirmed (as valid)\n"   , x_uid, a_owner);
      RPTG_FULL   fprintf (my.file_full, "      --       comparison       ");
      RPTG_FULL   fprintf (my.file_full, "   success     : can not predict\n");
      return 0;
   }
   /*---(look up owner)------------------*/
   p = getpwnam (a_owner);
   --rce;  if (p == NULL) {
      RPTG_FULL   fprintf (my.file_full, "   - %-9.9s : FAILED, invalid\n"   , a_owner);
      return rce;
   }
   /*---(save owner id)------------------*/
   x_uid = p->pw_uid;
   RPTG_FULL      fprintf (my.file_full, "%4d %-9.9s : confirmed (as valid)\n"   , x_uid, a_owner);
   /*===[[ TEST MATCH ]]=================*/
   RPTG_FULL      fprintf (my.file_full, "      --       comparison       ");
   /*---(test match)---------------------*/
   if (my.curr_stat.st_uid == x_uid) {
      RPTG_FULL   fprintf (my.file_full, "   success     : exact match, done\n");
      return 0;
   }
   /*---(check unforced miss)------------*/
   --rce;  if (a_mode != MODE_HAMMER && a_mode != MODE_FORCED && a_mode != MODE_UPDATE) {
      RPTG_FULL   fprintf (my.file_full, "   WARNING     : does not match (no force)\n");
      return rce;
   }
   /*---(attempt force)------------------*/
   RPTG_FULL      fprintf (my.file_full, "   UPDATE REQD : forced mode\n");
   RPTG_FULL      fprintf (my.file_full, "      --       updating         ");
   rc  = lchown (a_path, x_uid, -1);
   --rce;  if (rc < 0) {
      RPTG_FULL   fprintf (my.file_full, "   FAILED      : lchown rc negative\n");
      return rce;
   }
   RPTG_FULL      fprintf (my.file_full, "   complete    : chmod rc zero\n");
   /*===[[ RETEST ]]=====================*/
   /*---(reaquire the object)------------*/
   rc = CHECK__exist (31, a_path);
   --rce;  if (rc < 0) {
      return rce;
   }
   /*---(reaquire attributes)------------*/
   RPTG_FULL      fprintf (my.file_full, "      --       new actual       ");
   p   = getpwuid (my.curr_stat.st_uid);
   --rce;  if (p == NULL) {
      RPTG_FULL   fprintf (my.file_full, "   FAILED      : could not translate uid\n");
      return rce;
   }
   RPTG_FULL      fprintf (my.file_full, "%4d %-9.9s : confirmed (as valid)\n", my.curr_stat.st_uid, p->pw_name);
   strlcpy (u_aowner, p->pw_name, LEN_NAME);
   /*---(retest)-------------------------*/
   RPTG_FULL      fprintf (my.file_full, "      --       re-compare       ");
   --rce;  if (my.curr_stat.st_uid != x_uid) {
      RPTG_FULL   fprintf (my.file_full, "   FAILURE     : still does not match\n");
      return rce;
   }
   RPTG_FULL      fprintf (my.file_full, "   success     : exact match, done\n");
   /*---(complete)-----------------------*/
   --rce;
   return -(rce);
}

char         /*--> verify/change the group ---------------[ ------ [ ------ ]-*/
SET_group          (
      char       *a_path,     /* full path including name                     */
      char       *a_group,    /* group of filesystem object                   */
      char        a_mode)     /* mode is verify or create/update              */
{  /*---(locals)-----------+-----------+-*/
   tGROUP     *g           = NULL;
   char        rc          =   0;
   char        rce         = -10;
   int         x_gid       =  -1;
   char        x_gname     [LEN_NAME] = "n/a";
   /*---(defenses)-----------------------*/
   --rce;  if (a_path  == NULL) {
      return rce;
   }
   /*---(prepare)------------------------*/
   strlcpy (u_egroup, "---(NF)---", LEN_NAME);
   strlcpy (u_agroup, "---(NF)---", LEN_NAME);
   /*===[[ ACTUAL ]]=====================*/
   RPTG_FULL      fprintf (my.file_full, "      -- GROUP actual           ");
   /*---(look up actual)-----------------*/
   g = getgrgid (my.curr_stat.st_gid);
   --rce;  if (g == NULL) {
      RPTG_FULL   fprintf (my.file_full, "%4d %-9.9s : FAILED, invalid\n"    , my.curr_stat.st_gid, "(null)---");
      return rce;
   }
   RPTG_FULL      fprintf (my.file_full, "%4d %-9.9s : confirmed (as valid)\n", my.curr_stat.st_gid, g->gr_name);
   strlcpy (u_agroup, g->gr_name, LEN_NAME);
   /*===[[ EXPECT ]]=====================*/
   RPTG_FULL      fprintf (my.file_full, "      --       expected         ");
   /*---(defenses)-----------------------*/
   --rce;  if (a_group == NULL) {
      RPTG_FULL   fprintf (my.file_full, "   - %-9.9s : FAILED, null\n"      , "(null)---");
      return rce;
   }
   strlcpy (u_egroup, a_group, LEN_NAME);
   /*---(look up owner)------------------*/
   g = getgrnam (a_group);
   --rce;  if (g == NULL) {
      RPTG_FULL   fprintf (my.file_full, "   - %-9.9s : FAILED, invalid\n"   , a_group);
      return rce;
   }
   /*---(save owner id)------------------*/
   x_gid = g->gr_gid;
   RPTG_FULL      fprintf (my.file_full, "%4d %-9.9s : confirmed (as valid)\n"    , x_gid, a_group);
   /*===[[ TEST MATCH ]]=================*/
   RPTG_FULL      fprintf (my.file_full, "      --       comparison       ");
   /*---(test match)---------------------*/
   if (my.curr_stat.st_gid == x_gid) {
      RPTG_FULL   fprintf (my.file_full, "   success     : exact match, done\n");
      return 0;
   }
   /*---(check unforced miss)------------*/
   --rce;  if (a_mode != MODE_HAMMER && a_mode != MODE_FORCED && a_mode != MODE_UPDATE) {
      RPTG_FULL   fprintf (my.file_full, "   WARNING     : does not match (not in force/update mode)\n");
      return rce;
   }
   /*---(attempt force)------------------*/
   RPTG_FULL      fprintf (my.file_full, "   UPDATE REQD : forced mode\n");
   RPTG_FULL      fprintf (my.file_full, "      --       updating         ");
   rc  = lchown (a_path, -1, x_gid);
   --rce;  if (rc < 0) {
      RPTG_FULL   fprintf (my.file_full, "   FAILED      : lchown rc negative\n");
      return rce;
   }
   RPTG_FULL      fprintf (my.file_full, "   complete    : chmod rc zero\n");
   /*===[[ RETEST ]]=====================*/
   /*---(reaquire the object)------------*/
   rc = CHECK__exist (31, a_path);
   --rce;  if (rc < 0) {
      return rce;
   }
   /*---(reaquire attributes)------------*/
   RPTG_FULL      fprintf (my.file_full, "      --       new actual       ");
   g   = getgrgid (my.curr_stat.st_gid);
   --rce;  if (g == NULL) {
      RPTG_FULL   fprintf (my.file_full, "   FAILED      : could not translate uid\n");
      return rce;
   }
   RPTG_FULL   fprintf (my.file_full, "%4d %-9.9s : confirmed (as valid)\n", my.curr_stat.st_gid, g->gr_name);
   strlcpy (u_agroup, g->gr_name, LEN_NAME);
   /*---(retest)-------------------------*/
   RPTG_FULL      fprintf (my.file_full, "      --       re-compare       ");
   --rce;  if (my.curr_stat.st_gid != x_gid) {
      RPTG_FULL   fprintf (my.file_full, "   FAILURE     : still does not match\n");
      return rce;
   }
   RPTG_FULL      fprintf (my.file_full, "   success     : exact match, done\n");
   /*---(complete)-----------------------*/
   --rce;
   return -(rce);
}

char         /*--> interpret perms to ascii --------------[ ------ [ ------ ]-*/
SET_permtext       (
      /*----------+-----------+-----------------------------------------------*/
      char        a_type,     /* object type                                  */
      int         a_numeric,  /* perms in numeric                             */
      char       *a_text)     /* perms in ascii                               */
{  /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         a           = 0;             /* single perm octal digit        */
   char        x_type      = ' ';           /* entry type text                */
   char        x_perms     [LEN_NAME];      /* text representation of perms   */
   int         i           = 0;             /* generic iterator               */
   /*---(prepare)------------------------*/
   strlcat (x_perms, "---(NF)---"  , LEN_NAME);
   /*---(translate type)-----------------*/
   for (i = 0; i < MAX_VERB; ++i) {
      if (g_verbs [i].abbr != a_type) continue;
      x_type = g_verbs [i].perm;
   }
   --rce;  if (x_type == ' ') {
      if (a_text != NULL)  strlcpy (a_text, x_perms, LEN_NAME);
      return rce;
   }
   x_perms [0] = x_type;
   x_perms [1] = '\0';
   /*---(translate perms)----------------*/
   a = (a_numeric & 0000700) / 00100;
   strlcat (x_perms, g_permtext [a], LEN_NAME);
   a = (a_numeric & 0000070) / 00010;
   strlcat (x_perms, g_permtext [a], LEN_NAME);
   a = (a_numeric & 0000007);
   strlcat (x_perms, g_permtext [a], LEN_NAME);
   /*---(return)-------------------------*/
   if (a_text != NULL)  strlcpy (a_text, x_perms, LEN_NAME);
   return 0;
}

char         /*--> verify/change the permissions ---------[ ------ [ ------ ]-*/
SET_perms          (
      /*----------+-----------+-----------------------------------------------*/
      char       *a_path,     /* full path of directory including name        */
      char        a_abbr,     /* ffile type abbreviation                      */
      char       *a_perms,    /* correct permissions for directory            */
      char        a_mode)     /* mode is verify or create/update              */
{  /*---(locals)-----------+-----------+-*/
   char        rc          = 0;
   char        rce         = -10;
   char        x_perms     [LEN_NAME];
   int         x_value     = -1;
   int         x           = 0;
   int         i           = 0;
   /*---(defenses)-----------------------*/
   --rce;  if (a_path  == NULL) {
      return rce;
   }
   /*---(prepare)------------------------*/
   strlcpy (u_eperms, "---(bad)--", LEN_NAME);
   strlcpy (u_aperms, "---(n/a)--", LEN_NAME);
   /*===[[ ACTUAL ]]=====================*/
   RPTG_FULL      fprintf (my.file_full, "      -- PERMS actual         ");
   /*---(interpret)----------------------*/
   SET_permtext (a_abbr, my.curr_stat.st_mode, x_perms);
   strlcpy (u_aperms, x_perms, LEN_NAME);
   RPTG_FULL      fprintf (my.file_full, "%04o %-10.10s  : ", my.curr_stat.st_mode & 007777, x_perms);
   RPTG_FULL      fprintf (my.file_full, "confirmed (as valid)\n");
   /*===[[ EXPECT ]]=====================*/
   RPTG_FULL      fprintf (my.file_full, "      --       %-14.14s ", a_perms);
   /*---(interpret)----------------------*/
   for (i = 0; i < MAX_PERM; ++i) {
      if (strcmp (g_perms [i].name, a_perms) != 0)  continue;
      x_value = g_perms [i].value;
   }
   --rce;  if (x_value < 0) {
      RPTG_FULL   fprintf (my.file_full, "   FAILED      : not valid name\n");
      return rce;
   }
   SET_permtext (a_abbr, x_value, x_perms);
   RPTG_FULL      fprintf (my.file_full, "%04o %-10.10s  : ", x_value & 007777, x_perms);
   RPTG_FULL      fprintf (my.file_full, "confirmed (as valid)\n");
   strlcpy (u_eperms, x_perms, LEN_NAME);
   /*---(check match)--------------------*/
   RPTG_FULL      fprintf (my.file_full, "      --       comparison       ");
   if ((x_value & 007777) == (my.curr_stat.st_mode & 007777)) {
      RPTG_FULL   fprintf (my.file_full, "   success     : exact match, done\n");
      return 0;
   }
   /*---(check unforced miss)------------*/
   --rce;  if (a_mode != MODE_HAMMER && a_mode != MODE_FORCED && a_mode != MODE_UPDATE) {
      RPTG_FULL   fprintf (my.file_full, "   WARNING     : does not match (no force)\n");
      return -(rce);
   }
   /*---(attempt force)------------------*/
   RPTG_FULL      fprintf (my.file_full, "   UPDATE REQD : forced mode\n");
   RPTG_FULL      fprintf (my.file_full, "      --       updating         ");
   rc  = chmod (a_path, x_value);
   --rce;  if (rc < 0) {
      RPTG_FULL   fprintf (my.file_full, "   FAILED      : chmod rc negative\n");
      return rce;
   }
   RPTG_FULL      fprintf (my.file_full, "   complete    : chmod rc zero\n");
   /*---(reaquire the object)------------*/
   rc = CHECK__exist (31, a_path);
   --rce;  if (rc < 0) {
      return rce;
   }
   /*---(interpret)----------------------*/
   RPTG_FULL      fprintf (my.file_full, "      --       new actual     ");
   SET_permtext (a_abbr, my.curr_stat.st_mode, x_perms);
   strlcpy (u_aperms, x_perms, LEN_NAME);
   RPTG_FULL      fprintf (my.file_full, "%04o %-10.10s  : ", my.curr_stat.st_mode & 007777, x_perms);
   RPTG_FULL      fprintf (my.file_full, "confirmed (as valid)\n");
   /*---(retest)-------------------------*/
   RPTG_FULL      fprintf (my.file_full, "      --       re-compare       ");
   --rce;
   if ((x_value & 007777) != (my.curr_stat.st_mode & 007777)) {
      RPTG_FULL   fprintf (my.file_full, "   FAILED      : still does not match\n");
      return rce;
   }
   RPTG_FULL      fprintf (my.file_full, "   success     : exact match, done\n");
   /*---(complete)-----------------------*/
   --rce;
   return -(rce);
}

char
new_machine        (char *a_desc, char *a_name, char *a_type, char a_done)
{  /*---(locals)-----------+-----------+-*/
   char        x_temp      [500]       = "";
   char        x_machine   [100]       = "";
   char        x_type      [100]       = "";
   char        x_types     [500]       = " server desktop ";
   char        x_checks    = 5;  /* exist, type, owner, group, perms */
   char        x_passed    = 0;
   char        x_updates   = 0;
   char        x_warns     = 0;
   char        x_errors    = 0;
   int         i           = 0;
   char        rce         = -10;
   int         x_curr      = 0;
   char       *p;
   char       *q           = " ";
   char       *r           = NULL;
   /*---(header)-------------------------*/
   ++my.sub_checks;
   sprintf (x_temp, "   >> MACHINE   : %s =====================================================================", a_desc);
   RPTG_FULL   fprintf (my.file_full, "%-80.80s\n", x_temp);
   if (a_done == 'y')  {
      fprintf (my.file_full, "      -- will not add machine as it appears after other entries\n");
   }
   /*---(machine name)-------------------*/
   RPTG_FULL   fprintf (my.file_full, "      -- requested        ");
   /*---(defenses)-----------------------*/
   --rce;
   if (a_name == NULL) {
      RPTG_FULL   fprintf (my.file_full, "   - %-15.15s : WARNING, null\n\n", "(null)---");
      ++x_errors;
   } else {
      /*---(look up machine)-------------*/
      --rce;
      x_curr = -1;
      for (i = 0; i < nmachine; ++i) {
         if (strcmp (a_name, machines [i].name) == 0) {
            x_curr = i;
            break;
         }
      }
      if (x_curr >= 0) {
         RPTG_FULL   fprintf (my.file_full, "%4d %-15.15s : WARNING, duplicate\n\n", x_curr, a_name);
         ++x_errors;
      } else {
         /*---(save machine)-------------*/
         strcpy (machines [nmachine].name, a_name);
         strcpy (machines [nmachine].types, "");
         RPTG_FULL   fprintf (my.file_full, "%4d %-15.15s : confirmed (as valid)\n"    , nmachine, a_name);
         ++nmachine;
      }
   }
   /*---(types)--------------------------*/
   --rce;
   if (a_type == NULL) {
      RPTG_FULL   fprintf (my.file_full, "      -- type              %-19.19s : WARNING, null\n\n", "(null)---");
      ++x_errors;
   } else {
      /*---(parse types)-----------------*/
      strcpy (x_temp, a_type);
      p = strtok_r (x_temp, q, &r);
      strcpy (machines [nmachine - 1].types, " ");
      while (1) {
         if (p == NULL)   break;
         ySTR_trim (p, ySTR_BOTH);
         RPTG_FULL   fprintf (my.file_full, "      -- type              %-19.19s : "    , p);
         sprintf (x_type, " %s ", p);
         if (strstr (x_types, x_type) != NULL) {
            RPTG_FULL   fprintf (my.file_full, "confirmed (as valid)\n");
            strcat (machines [nmachine - 1].types, p);
            strcat (machines [nmachine - 1].types, " ");
         } else {
            RPTG_FULL   fprintf (my.file_full, "WARNING, not valid\n");
            ++x_errors;
         }
         p = strtok_r (NULL, q, &r);
      }
   }
   /*---(check for current)--------------*/
   if (strcmp (my.host, machines [nmachine - 1].name) == 0) {
      strcpy (my.conf_machs, machines [nmachine - 1].types);
      RPTG_FULL   fprintf (my.file_full, "      *** this is the current host ***\n");
   }
   RPTG_summ   (x_checks, x_passed, x_updates, x_warns, x_errors);
   /*> RPTG_single (my.verb, a_desc, a_mode, s_checks, s_passed, s_updates, s_warns, s_errors);   <*/
   /*---(complete)-----------------------*/
   return 0;
}

char
new_user           (char *a_desc, char *a_name, char *a_type, char a_done)
{  /*---(locals)-----------+-----------+-*/
   struct      passwd     *p;
   char        rc          = 0;
   char        rce         = -10;
   int         x_uid       = -1;
   char        x_types     [500] = " full_user specialty storage ";
   char        x_type      [ 50];
   int         i           = 0;
   int         x_value     = -1;
   char        x_temp      [500]       = "";
   char        x_checks    = 0;  /* unknown */
   char        x_passed    = 0;
   char        x_updates   = 0;
   char        x_warns     = 0;
   char        x_errors    = 0;
   /*---(header)-------------------------*/
   ++my.sub_checks;
   sprintf (x_temp, "   >> USER      : %s =====================================================================", a_desc);
   RPTG_FULL   fprintf (my.file_full, "%-80.80s\n", x_temp);
   if (a_done == 'y')  {
      fprintf (my.file_full, "      -- will not add user as it appears after other entries\n");
   }
   /*---(user name)----------------------*/
   RPTG_FULL   fprintf (my.file_full, "      -- requested        ");
   /*---(defenses)-----------------------*/
   --rce;
   if (a_name == NULL) {
      RPTG_FULL   fprintf (my.file_full, "   - %-15.15s : WARNING, null\n\n", "(null)---");
      ++x_errors;
   } else {
      /*---(look up owner)------------------*/
      --rce;
      p = getpwnam (a_name);
      if (p == NULL) {
         RPTG_FULL   fprintf (my.file_full, "   - %-15.15s : WARNING, invalid\n\n", a_name);
         ++x_errors;
      } else {
         /*---(check for duplicate)------------*/
         --rce;
         for (i = 0; i < MAX_USERS; ++i) {
            if (strcmp (users [i].name, a_name) != 0)  continue;
            x_value = i;
         }
         if (x_value >= 0) {
            RPTG_FULL   fprintf (my.file_full, "%4d %-15.15s : WARNING, duplicate\n\n", p->pw_uid, a_name);
            ++x_errors;
         } else {
            /*---(save owner id)------------------*/
            x_uid = p->pw_uid;
            RPTG_FULL   fprintf (my.file_full, "%4d %-15.15s : confirmed (as valid)\n"    , x_uid, a_name);
         }
      }
   }
   /*---(type)---------------------------*/
   RPTG_FULL   fprintf (my.file_full, "      -- type             ");
   /*---(defenses)-----------------------*/
   --rce;
   if (a_type == NULL) {
      RPTG_FULL   fprintf (my.file_full, "%-15.15s      : WARNING, null\n\n", "(null)---");
      ++x_errors;
   } else {
      --rce;
      sprintf (x_type, " %s ", a_type);
      if (strstr (x_types, x_type) == NULL) {
         RPTG_FULL   fprintf (my.file_full, "%-15.15s      : WARNING, type not legal\n\n", a_type);
         ++x_errors;
      } else {
         RPTG_FULL   fprintf (my.file_full, "%-15.15s      : confirmed (as valid)\n"    , a_type);
         /*---(save)---------------------------*/
         if (a_done != 'y') {
            strcpy (users [nusers].name, a_name);
            strcpy (users [nusers].type, a_type);
            ++nusers;
            RPTG_FULL   fprintf (my.file_full, "      -- now have %d users\n", nusers);
         } else {
            RPTG_FULL   fprintf (my.file_full, "      -- still have %d users\n", nusers);
         }
      }
   }
   RPTG_summ   (x_checks, x_passed, x_updates, x_warns, x_errors);
   /*> RPTG_single (my.verb, a_desc, a_mode, s_checks, s_passed, s_updates, s_warns, s_errors);   <*/
   /*---(complete)-----------------------*/
   return -x_errors;
}



/*====================------------------------------------====================*/
/*===----                    unit testing accessor                     ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char*            /* [------] unit test accessor ------------------------------*/
SET_unit           (char *a_question, int a_num)
{
   /*---(prepare)------------------------*/
   strlcpy  (unit_answer, "SET_unit         : question not understood", LEN_UNIT);
   /*---(actuals)------------------------*/
   if        (strncmp (a_question, "act_owner"       , 20)   == 0) {
      snprintf (unit_answer, LEN_UNIT, "SET_act_owner    : %.35s"         , u_aowner     );
   } else if (strncmp (a_question, "act_group"       , 20)   == 0) {
      snprintf (unit_answer, LEN_UNIT, "SET_act_group    : %.35s"         , u_agroup     );
   } else if (strncmp (a_question, "act_perms"       , 20)   == 0) {
      snprintf (unit_answer, LEN_UNIT, "SET_act_perms    : %.35s"         , u_aperms     );
   }
   /*---(fields)-------------------------*/
   if        (strncmp (a_question, "exp_owner"      , 20)   == 0) {
      snprintf (unit_answer, LEN_UNIT, "SET_exp_owner    : %.35s"         , u_eowner     );
   } else if (strncmp (a_question, "exp_group"      , 20)   == 0) {
      snprintf (unit_answer, LEN_UNIT, "SET_exp_group    : %.35s"         , u_egroup     );
   } else if (strncmp (a_question, "exp_perms"      , 20)   == 0) {
      snprintf (unit_answer, LEN_UNIT, "SET_exp_perms    : %.35s"         , u_eperms     );
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}



/*============================[[ end-of-code ]]===============================*/
