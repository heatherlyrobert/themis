/*============================[[    beg-code    ]]============================*/
#include    "themis.h"


static FILE *s_file = NULL;
static char  s_name [LEN_PATH] = "";
static char  s_focus = FOCUS_ALL;


tUSERS      users [MAX_USERS];
int         nusers = 0;
int         cuser  = -1;



tMACH       machines [MAX_MACH];
int         nmachine = 0;


int         s_area   = 0;
int         s_step   = 0;
int         s_pass   = 0;
int         s_fail   = 0;
int         s_badd   = 0;
int         s_modd   = 0;


const tVERB  g_verbs [MAX_VERB] = {
   /*---  --------  ------------------------------------------  -------------------  -------------------  ---   --- */
   { 'a', "area"    , "grouping of actions"                   , "AREA"             , "---"              , ' ' , '-'},
   { 'b', "block"   , "block kernel device"                   , "BLOCK DEVICE"     , "block_dev"        , 'b' , 'y'},
   { 'c', "char"    , "character kernel device"               , "CHAR DEVICE"      , "char_dev"         , 'c' , 'y'},
   { 'd', "dir"     , "filesystem directory"                  , "DIRECTORY"        , "directory"        , 'd' , 'y'},
   { 'e', "end"     , "end of entries"                        , "END"              , "---"              , ' ' , '-'},
   { 'f', "file"    , "regular file"                          , "REG FILE"         , "reg_file"         , '-' , 'y'},
   { 'g', "group"   , "user group entry"                      , "GROUP"            , "group"            , '-' , '-'},
   { 'h', "hard"    , "hard filesystem link"                  , "HARD LINK"        , "---"              , '-' , 'y'},
   { 'i', "ipsoc"   , "internet socket"                       , "SOCKET"           , "socket"           , 's' , 'y'},
   { 'm', "mach"    , "machine inventory entry"               , "MACHINE"          , "---"              , ' ' , '-'},
   { 'p', "pipe"    , "fifo pipe"                             , "PIPE"             , "fifo"             , 'p' , 'y'},
   { 's', "sym"     , "symbolic filesystem link"              , "SYM LINK"         , "sym_link"         , 'l' , 'y'},
   { 'u', "user"    , "user inventory entry"                  , "USER"             , "---"              , ' ' , '-'},
   { '-', "-------" , "end-of-entries"                        , "---"              , "---"              , '-' , '-'},
   /*---  --------  ------------------------------------------  -------------------  -------------------  ---   --- */
};

static char   s_nverb = 0;
static char   s_valid     [LEN_FULL]   = "";
char          g_norms     [LEN_LABEL]  = "";



/*====================------------------------------------====================*/
/*===----                      program level                           ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char
CONF_init               (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   char        t           [LEN_TERSE] = "";
   /*---(header)-------------------------*/
   DEBUG_CONF   yLOG_enter   (__FUNCTION__);
   /*---(defaults)-----------------------*/
   s_file = NULL;
   ystrlcpy (s_name, "", LEN_PATH);
   ystrlcpy (s_valid, " ", LEN_FULL);
   ystrlcpy (g_norms, "", LEN_LABEL);
   s_nverb = 0;
   /*---(valid verbs)--------------------*/
   for (i = 0; i < MAX_VERB; ++i) {
      if (g_verbs [i].abbr == '-')  break;
      ystrlcat (s_valid, g_verbs [i].name, LEN_FULL);
      ystrlcat (s_valid, " ", LEN_FULL);
      ++s_nverb;
      sprintf (t, "%c", g_verbs [i].abbr);
      ystrlcat (g_norms, t, LEN_LABEL);
   }
   /*---(complete)-----------------------*/
   DEBUG_CONF   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        file handling                         ----===*/
/*====================------------------------------------====================*/
static void      o___FILE____________________o (void) {;}

char         /*--> prepare configuration -----------------[ leaf   [ ------ ]-*/
CONF__open              (cchar a_name [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   struct      stat        s;
   char        x_name      [LEN_STR];
   /*---(header)-------------------------*/
   DEBUG_CONF   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_CONF   yLOG_point   ("s_file"    , s_file);
   --rce;  if (s_file != NULL) {
      DEBUG_CONF   yLOG_note    ("configuration file already open");
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF   yLOG_info    ("a_name"    , a_name);
   /*---(check config name)--------------*/
   DEBUG_CONF   yLOG_note    ("check configuration file name");
   snprintf (x_name         , LEN_STR, "%s%s", DIR_ETC  , FILE_CONF );
   DEBUG_CONF   yLOG_info    ("expecting" , x_name);
   --rce;  if (strcmp (x_name, a_name) == 0) {
      DEBUG_CONF   yLOG_note    ("main configuration file in use");
   } else {
      DEBUG_CONF   yLOG_note    ("not using main configuration file");
      snprintf (x_name         , LEN_STR, "%s%s", DIR_TEST , FILE_CONF );
      DEBUG_CONF   yLOG_info    ("now test"  , x_name);
      if (strcmp (x_name, a_name) == 0) {
         DEBUG_CONF   yLOG_note    ("working in testing environment");
      } else {
         DEBUG_CONF   yLOG_note    ("not working in testing environment");
         /*> DEBUG_CONF   yLOG_fatal   ("conf file" , "configuration file name not allowed");   <*/
         DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(check config existance)---------*/
   DEBUG_CONF   yLOG_note    ("check configuration existance");
   rc = lstat (a_name, &s);
   --rce;  if  (rc < 0) {
      /*> DEBUG_CONF   yLOG_fatal   ("conf file" , "configuration file not found");   <*/
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF   yLOG_note    ("configuration file found");
   /*---(check config file type)---------*/
   DEBUG_CONF   yLOG_note    ("check configuration file type");
   --rce;  if  (!S_ISREG(s.st_mode))  {
      /*> DEBUG_CONF   yLOG_fatal   ("conf file" , "configuration not regular file type");   <*/
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF   yLOG_note    ("configuration is a regular file type");
   /*---(check owner)--------------------*/
   DEBUG_CONF   yLOG_note    ("check configuration owner");
   --rce;  if  (s.st_uid  != 0)  {
      /*> DEBUG_CONF   yLOG_fatal   ("conf file" , "configuration owner not root");   <*/
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF   yLOG_note    ("configuration owner is root");
   /*---(check group)--------------------*/
   DEBUG_CONF   yLOG_note    ("check configuration group");
   --rce;  if  (s.st_gid  != 0)  {
      /*> DEBUG_CONF   yLOG_fatal   ("conf file" , "configuration group not root");   <*/
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF   yLOG_note    ("configuration group is root");
   /*---(check config permissions)-------*/
   DEBUG_CONF   yLOG_note    ("check configuration permissions");
   --rce;  if  ((s.st_mode & 00777) != 00600)  {
      /*> DEBUG_CONF   yLOG_fatal   ("conf file" , "configuration permissions not 0600");   <*/
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF   yLOG_note    ("configuration permissions are 0600");
   /*---(open configuration)-------------*/
   s_file = fopen (a_name, "r");
   DEBUG_CONF   yLOG_point   ("s_file"    , s_file);
   --rce;  if (s_file == NULL) {
      /*> DEBUG_CONF   yLOG_fatal   ("conf file" , "can not open configuration file");   <*/
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF   yLOG_note    ("configuration file open");
   /*---(save)---------------------------*/
   my.file_conf = s_file;
   ystrlcpy (s_name, a_name, LEN_PATH);
   /*---(complete)-----------------------*/
   DEBUG_CONF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
CONF__close             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_CONF   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_CONF   yLOG_point   ("s_file"    , s_file);
   --rce;  if (s_file == NULL) {
      DEBUG_CONF   yLOG_note    ("configuration is not open");
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(close)--------------------------*/
   rc = fclose (s_file);
   DEBUG_CONF   yLOG_value   ("fclose"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(ground)-------------------------*/
   s_file = my.file_conf = NULL;
   ystrlcpy (s_name, "", LEN_PATH);
   /*---(complete)-----------------------*/
   DEBUG_CONF   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      reading file                            ----===*/
/*====================------------------------------------====================*/
static void      o___READ____________________o (void) {;}

char         /*--> read config record --------------------[ leaf   [ ------ ]-*/
CONF__read              (char r_recd [LEN_RECD])
{
   /*---(locals)-----------+-----------+-*/
   int         rc          = 0;             /* generic return code            */
   char        rce         = -10;           /* return code for errors         */
   char        x_recd      [LEN_RECD];
   int         x_len       = 0;             /* input record length            */
   char        x_temp      [20];
   int         i           = 0;
   /*---(header)-------------------------*/
   DEBUG_CONF   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   my.recd [0] = '\0';
   if (r_recd != NULL)  r_recd [0] = '\0';
   /*---(defense)------------------------*/
   DEBUG_CONF   yLOG_point   ("s_file"    , s_file);
   --rce;  if (s_file == NULL) {
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF   yLOG_point   ("r_recd"    , s_file);
   --rce;  if (r_recd == NULL) {
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (feof (s_file)) {
      DEBUG_CONF   yLOG_note    ("already at end of file");
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(read for a good record)---------*/
   --rce;
   while (1) {
      /*---(read next)-------------------*/
      DEBUG_CONF   yLOG_note    ("read configuration file");
      fgets (x_recd, LEN_RECD, s_file);
      if (feof (s_file)) {
         DEBUG_CONF   yLOG_note    ("hit end of file");
         break;
      }
      ++my.lines;
      DEBUG_CONF   yLOG_value   ("line#"     , my.lines);
      /*---(filter)----------------------*/
      if (x_recd [0] == '\0') {
         DEBUG_CONF   yLOG_note    ("blank line");
         CONF__unfocus ();
         continue;
      }
      if (x_recd [0] == '#') {
         DEBUG_CONF   yLOG_note    ("comment line");
         /*> CONF__unfocus ();                                                        <*/
         continue;
      }
      x_len = strlen (x_recd);
      DEBUG_CONF   yLOG_value   ("length"    , x_len);
      if (x_len <= 10)  {
         CONF__unfocus ();
         DEBUG_CONF   yLOG_note    ("too short, skipping");
         continue;
      }
      /*---(fix end)---------------------*/
      x_recd [--x_len] = '\0';
      if (x_recd [0] == '#') {
         /*> CONF__unfocus ();                                                        <*/
         DEBUG_CONF   yLOG_note    ("comment, skipping");
         continue;
      }
      /*---(copy)------------------------*/
      DEBUG_CONF   yLOG_note    ("save copy of source record");
      ystrlcpy (r_recd , x_recd, LEN_RECD);
      ystrlcpy (my.recd, x_recd, LEN_RECD);
      my.len   = x_len;
      /*---(return)----------------------*/
      DEBUG_CONF   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   DEBUG_CONF   yLOG_note    ("got a good record");
   /*---(check for trouble)--------------*/
   --rce;  if (my.lines <= 0) {
      DEBUG_CONF   yLOG_note    ("empty file");
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_CONF   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      parsing input                           ----===*/
/*====================------------------------------------====================*/
static void      o___PARSE___________________o (void) {;}

char         /*--> clean a config record -----------------[ leaf   [ ------ ]-*/
CONF__clear             (void)
{
   DEBUG_CONF   yLOG_senter  (__FUNCTION__);
   my.abbr            = '-';
   ystrlcpy (my.verb  , "" , LEN_TERSE);
   ystrlcpy (my.desc  , "" , LEN_DESC);
   my.act             = ACT_WHAT;
   my.imp             = '�';
   my.mach            = '�';
   ystrlcpy (my.target, "" , LEN_HUND);
   ystrlcpy (my.own   , "�", LEN_TERSE);
   my.e_uid           = -1;
   ystrlcpy (my.grp   , "�", LEN_TERSE);
   my.e_gid           = -1;
   ystrlcpy (my.perms , "�", LEN_TERSE);
   my.e_mode          = -1;
   my.type            = '�';
   ystrlcpy (my.source, "" , LEN_HUND);
   my.e_major         = -1;
   my.e_minor         = -1;
   my.exists = '-';
   stat ("/nowheresville", &my.curr_stat);
   ystrlcpy (g_check, "�   ������� �   ���������� �   ���������� �   ���������� �   �", LEN_HUND);
   DEBUG_CONF   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
CONF__verb         (char a_pos, cchar a_verb [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         i           =    0;
   int         l           =    0;
   char        x_verb      [LEN_TERSE] = "";
   /*---(header)-------------------------*/
   DEBUG_CONF   yLOG_senter  (__FUNCTION__);
   /*---(default)------------------------*/
   my.abbr = '-';
   ystrlcpy (my.verb, "" , LEN_TERSE);
   ystrlcpy (my.title, "", LEN_DESC);
   /*---(defense)------------------------*/
   DEBUG_CONF   yLOG_spoint  (a_verb);
   --rce;  if (a_verb == NULL) {
      g_check [a_pos] = '�';
      DEBUG_CONF   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   ystrlcpy  (x_verb, a_verb, LEN_TERSE);
   ystrltrim (x_verb, ySTR_BOTH, LEN_TERSE);
   DEBUG_CONF   yLOG_snote   (x_verb);
   l = strlen (x_verb);
   DEBUG_CONF   yLOG_sint    (l);
   --rce;  if (l == 0) {
      g_check [a_pos] = '�';
      DEBUG_CONF   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (l < 3) {
      g_check [a_pos] = '<';
      DEBUG_CONF   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(search)-------------------------*/
   my.abbr = '-';
   for (i = 0; i < MAX_VERB; ++i) {
      if (g_verbs [i].abbr     == '-')              break;
      if (strcmp (g_verbs [i].name, x_verb) != 0)   continue;
      my.abbr = g_verbs [i].abbr;
      ystrlcpy (my.verb , g_verbs [i].name , LEN_TERSE);
      ystrlcpy (my.title, g_verbs [i].title, LEN_DESC);
      g_check [a_pos] = my.abbr;
      DEBUG_CONF   yLOG_snote   ("FOUND");
      DEBUG_CONF   yLOG_sexit   (__FUNCTION__);
      return 1;
   }
   /*---(complete)-----------------------*/
   DEBUG_CONF   yLOG_snote   ("not found");
   g_check [a_pos] = '?';
   --rce;
   /*---(complete)-----------------------*/
   DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
   return rce;
}

char         /*--> read config record --------------------[ leaf   [ ------ ]-*/
CONF__parse             (char a_pos, cchar a_recd [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_recd      [LEN_RECD];
   char        x_verbs     [LEN_RECD]  = " area block char dir file mach user sym end ";
   char       *p;
   char       *q           = "\x1F";
   char       *r           = NULL;
   char        x_temp      [20];
   int         i           =    0;
   int         l           =    0;
   int         c           =    0;
   char       *x_field     = NULL;
   char        n           =    0;
   char        x_sum       = END_PARSE;
   /*---(header)-------------------------*/
   DEBUG_CONF   yLOG_enter   (__FUNCTION__);
   /*---(defaults)--------------------*/
   CONF__clear ();
   n = a_pos;
   /*---(defense)------------------------*/
   DEBUG_CONF   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      g_check [x_sum] = '�';
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF   yLOG_info    ("a_recd"    , a_recd);
   l = strlen (a_recd);
   DEBUG_CONF   yLOG_value   ("l"         , l);
   --rce;  if (l < 50) {
      DEBUG_CONF   yLOG_note    ("len too short");
      g_check [x_sum] = '�';
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF   yLOG_value   ("length"    , my.len);
   c = ystrldcnt (a_recd, '', LEN_RECD);
   DEBUG_PROG   yLOG_value   ("c"         , c);
   --rce;  if (c < 11 || c > 12) {
      g_check [x_sum] = '�';
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create a copy of recd)----------*/
   DEBUG_CONF   yLOG_note    ("create a copy of source record");
   ystrlcpy (x_recd, a_recd, LEN_RECD);
   DEBUG_CONF   yLOG_info    ("x_recd"    , x_recd);
   /*---(get verb)-----------------------*/
   p = strtok_r (x_recd, q, &r);
   DEBUG_CONF   yLOG_point   ("*p"        , p);
   --rce;  if (p == NULL) {
      DEBUG_CONF   yLOG_note    ("strtok_r came up empty");
      g_check [x_sum] = '�';
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = CONF__verb (0, p);
   --rce;  if (rc <= 0) {
      DEBUG_CONF   yLOG_note    ("verb not found");
      g_check [x_sum] = '!';
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(read fields)--------------------*/
   for (i = 1; i < 20; ++i) {
      DEBUG_CONF   yLOG_note    ("read next field");
      p = strtok_r (NULL  , q, &r);
      --rce;  if (p == NULL) {
         DEBUG_CONF   yLOG_note    ("strtok_r came up empty");
         break;
      }
      l = strlen (p);
      DEBUG_CONF   yLOG_value   ("l"         , l);
      ystrltrim (p, ySTR_BOTH, l);
      DEBUG_CONF   yLOG_info    ("p"         , p);
      if      (p[0] == '-')  p[0] = '\0';
      else if (p[0] == '�')  p[0] = '\0';
      DEBUG_CONF   yLOG_info    ("p"         , p);
      l = strlen (p);
      DEBUG_CONF   yLOG_value   ("l"         , l);
      switch (i) {
      case  1 :
         if (l > 0) {
            ystrlcpy (my.desc      , p, LEN_STR);
            g_check [++n] = 'd';
         } else g_check [++n] = '-';
         DEBUG_CONF   yLOG_info    ("desc"      , my.desc);
         break;
      case  2 :
         DEBUG_CONF   yLOG_char    ("act"       , my.act);
         if (l > 0)  {
            switch (p [0]) {
            case 'A'  :  my.act = ACT_ADD;   break;
            case 'u'  :  my.act = ACT_FIX;   break;
            case 'x'  :  my.act = ACT_DEL;   break;
            case '-'  :  my.act = ACT_NONE;  break;
            default   :  my.act = ACT_WHAT;  break;
            }
         } else my.act = ACT_NONE;
         DEBUG_CONF   yLOG_char    ("act"       , my.act);
         break;
      case  3 :  
         DEBUG_CONF   yLOG_char    ("imp"       , my.imp);
         if (l > 0)  my.imp        = p [0];
         DEBUG_CONF   yLOG_char    ("imp"       , my.imp);
         break;
      case  4 :  
         DEBUG_CONF   yLOG_char    ("mach"      , my.mach);
         if (l > 0)  my.mach       = p [0];
         DEBUG_CONF   yLOG_char    ("mach"      , my.mach);
         break;
      case  5 :  
         DEBUG_CONF   yLOG_info    ("target"    , my.target);
         if (l > 0) {
            ystrlcpy (my.target    , p, LEN_HUND);
            g_check [++n] = 't';
         } else g_check [++n] = '-';
         DEBUG_CONF   yLOG_info    ("target"    , my.target);
         break;
      case  6 :  
         DEBUG_CONF   yLOG_info    ("own"       , my.own);
         if (l > 0) {
            ystrlcpy (my.own       , p, LEN_TERSE);
            g_check [++n] = 'o';
         } else g_check [++n] = '-';
         DEBUG_CONF   yLOG_info    ("own"       , my.own);
         break;
      case  7 :  
         DEBUG_CONF   yLOG_info    ("grp"       , my.grp);
         if (l > 0) {
            ystrlcpy (my.grp       , p, LEN_TERSE);
            g_check [++n] = 'g';
         } else g_check [++n] = '-';
         DEBUG_CONF   yLOG_info    ("grp"       , my.grp);
         break;
      case  8 :  
         DEBUG_CONF   yLOG_info    ("perms"     , my.perms);
         if (l > 0) {
            ystrlcpy (my.perms     , p, LEN_TERSE);
            g_check [++n] = 'p';
         } else g_check [++n] = '-';
         DEBUG_CONF   yLOG_info    ("perms"     , my.perms);
         break;
      case  9 :  
         DEBUG_CONF   yLOG_char    ("type"      , my.type);
         if (l > 0) {
            my.type       = p [0];
            g_check [++n] = 't';
         } else g_check [++n] = '-';
         DEBUG_CONF   yLOG_char    ("type"      , my.type);
         break;
      case 10 :  
         DEBUG_CONF   yLOG_info    ("source"    , my.source);
         if (l > 0) {
            ystrlcpy (my.source    , p, LEN_HUND);
            g_check [++n] = 's';
         } else g_check [++n] = '-';
         DEBUG_CONF   yLOG_info    ("source"    , my.source);
         break;
      case 11 :  
         DEBUG_CONF   yLOG_info    ("reason"    , my.reason);
         if (l > 0)  ystrlcpy (my.reason    , p, LEN_HUND);
         DEBUG_CONF   yLOG_info    ("reason"    , my.reason);
         break;
      }
   } 
   DEBUG_CONF   yLOG_note    ("done parsing fields");
   /*---(troubles)-----------------------*/
   DEBUG_CONF   yLOG_value   ("i"         , i);
   --rce;  if (i < 11) {
      DEBUG_CONF   yLOG_note    ("not enough fields");
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(finalize)-----------------------*/
   DEBUG_CONF   yLOG_info    ("g_check"   , g_check);
   DEBUG_CONF   yLOG_char    ("my.act"    , my.act);
   DEBUG_CONF   yLOG_char    ("my.abbr"   , my.abbr);
   g_check [x_sum] = '!';
   /*---(additions)---------*/
   if (strchr (ACT_UPDATES, my.act) != NULL) {
      DEBUG_CONF   yLOG_note    ("A) addition");
      switch (my.abbr) {
      case 'a' :  if (strncmp (g_check, "a   d------", 11) == 0)  g_check [x_sum] = 'y';   break;
      case 'b' :  if (strncmp (g_check, "b   dtogp-s", 11) == 0)  g_check [x_sum] = 'y';   break;
      case 'c' :  if (strncmp (g_check, "c   dtogp-s", 11) == 0)  g_check [x_sum] = 'y';   break;
      case 'd' :  if (strncmp (g_check, "d   dtogp--", 11) == 0)  g_check [x_sum] = 'y';   break;
      case 'e' :  if (strncmp (g_check, "e   -------", 11) == 0)  g_check [x_sum] = 'y';   break;
      case 'f' :  if (strncmp (g_check, "f   dtogp--", 11) == 0)  g_check [x_sum] = 'y';   break;
      case 'g' :  if (strncmp (g_check, "g   dt-gp--", 11) == 0)  g_check [x_sum] = 'y';   break;
      case 'h' :  if (strncmp (g_check, "h   dt---ts", 11) == 0)  g_check [x_sum] = 'y';   break;
      case 'i' :  if (strncmp (g_check, "i   dtogp--", 11) == 0)  g_check [x_sum] = 'y';   break;
      case 'm' :  if (strncmp (g_check, "m   dt-----", 11) == 0)  g_check [x_sum] = 'y';   break;
      case 'p' :  if (strncmp (g_check, "p   dtogp--", 11) == 0)  g_check [x_sum] = 'y';   break;
      case 's' :  if (strncmp (g_check, "s   dt---ts", 11) == 0)  g_check [x_sum] = 'y';   break;
      case 'u' :  if (strncmp (g_check, "u   dto-p--", 11) == 0)  g_check [x_sum] = 'y';   break;
      default  :
                     DEBUG_CONF   yLOG_note    ("no handler found");
                     break;
      }
   }
   /*---(removals)----------*/
   else if (my.act == ACT_DEL) {
      DEBUG_CONF   yLOG_note    ("x) delete");
      switch (my.abbr) {
      case 'b' :  if (strncmp (g_check, "b   dt-----", 11) == 0)  g_check [x_sum] = 'y';   break;
      case 'c' :  if (strncmp (g_check, "c   dt-----", 11) == 0)  g_check [x_sum] = 'y';   break;
      case 'd' :  if (strncmp (g_check, "d   dt-----", 11) == 0)  g_check [x_sum] = 'y';   break;
      case 'f' :  if (strncmp (g_check, "f   dt-----", 11) == 0)  g_check [x_sum] = 'y';   break;
      case 'g' :  if (strncmp (g_check, "g   dt-----", 11) == 0)  g_check [x_sum] = 'y';   break;
      case 'h' :  if (strncmp (g_check, "h   dt-----", 11) == 0)  g_check [x_sum] = 'y';   break;
      case 'i' :  if (strncmp (g_check, "i   dt-----", 11) == 0)  g_check [x_sum] = 'y';   break;
      case 'p' :  if (strncmp (g_check, "p   dt-----", 11) == 0)  g_check [x_sum] = 'y';   break;
      case 's' :  if (strncmp (g_check, "s   dt-----", 11) == 0)  g_check [x_sum] = 'y';   break;
      case 'u' :  if (strncmp (g_check, "u   dt-----", 11) == 0)  g_check [x_sum] = 'y';   break;
      default  :
                     DEBUG_CONF   yLOG_note    ("no handler found");
                     break;
      }
   }
   /*---(no action)---------*/
   if (my.act == ACT_NONE) {
      DEBUG_CONF   yLOG_note    ("-) no action requested");
      g_check [x_sum] = 'y';
   }
   /*---(unknown)-----------*/
   else {
      DEBUG_CONF   yLOG_note    ("UNKNOWN ACTION");
   }
   /*---(handle outcome------------------*/
   DEBUG_CONF   yLOG_char    ("check"     , g_check [x_sum]);
   --rce;  if (g_check [x_sum] != 'y') {
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF   yLOG_char    ("my.act"    , my.act);
   --rce;  if (my.act == ACT_WHAT) {
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   g_check [2] = my.act;
   /*---(complete)-----------------------*/
   DEBUG_CONF   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         driver                               ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVER__________________o (void) {;}

char
CONF__ready             (void)
{
   DEBUG_CONF   yLOG_senter  (__FUNCTION__);
   DEBUG_CONF   yLOG_snote   (my.area);
   if (strcmp (my.area, "") == 0)    s_focus = FOCUS_ALL;
   else                              s_focus = FOCUS_NOT;
   DEBUG_CONF   yLOG_schar   (s_focus);
   DEBUG_CONF   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
CONF__focus             (char a_abbr, cchar a_desc [LEN_DESC])
{
   char        x_area      [LEN_TERSE];
   char       *p           = NULL;
   DEBUG_CONF   yLOG_senter  (__FUNCTION__);
   DEBUG_CONF   yLOG_schar   (s_focus);
   if (s_focus == FOCUS_ALL) {
      DEBUG_CONF   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   if (s_focus == FOCUS_YES) {
      s_focus = FOCUS_NOT;
      DEBUG_CONF   yLOG_schar   (s_focus);
      DEBUG_CONF   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   DEBUG_CONF   yLOG_snote   (a_desc);
   DEBUG_CONF   yLOG_schar   (a_desc [0]);
   if (a_desc [0] != '(') {
      DEBUG_CONF   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   ystrlcpy (x_area, a_desc + 1, LEN_TERSE);
   DEBUG_CONF   yLOG_snote   (x_area);
   p = strchr (x_area, ')');
   DEBUG_CONF   yLOG_spoint  (p);
   if (p == NULL) {
      DEBUG_CONF   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   p [0] = '\0';
   if (strcmp (my.area, x_area) == 0)  s_focus = FOCUS_YES;
   DEBUG_CONF   yLOG_schar   (s_focus);
   DEBUG_CONF   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
CONF__unfocus           (void)
{
   DEBUG_CONF   yLOG_senter  (__FUNCTION__);
   DEBUG_CONF   yLOG_schar   (s_focus);
   switch (s_focus) {
   case FOCUS_ALL :  break;
   case FOCUS_NOT :  break;
   case FOCUS_YES :  s_focus = FOCUS_NOT;  break;
   }
   DEBUG_CONF   yLOG_schar   (s_focus);
   DEBUG_CONF   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
CONF_driver             (cchar a_name [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_recd      [LEN_RECD];
   int         n           =   -1;
   int         x_len       =    0;
   time_t      time_date;
   tTIME      *curr_time   = NULL;
   char        t           [LEN_HUND]  = "";
   int         x_pass      =    0;
   int         x_fail      =    0;
   int         x_badd      =    0;
   int         x_modd      =    0;
   /*---(header)-------------------------*/
   DEBUG_CONF   yLOG_enter   (__FUNCTION__);
   /*---(open file)----------------------*/
   rc = CONF__open  (a_name);
   DEBUG_CONF   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   CONF__ready ();
   /*---(title)--------------------------*/
   printf ("%s\n", P_ONELINE);
   RPTG_FULL   printf ("   purpose    : %s\n", P_PURPOSE);
   /*---(host name)----------------------*/
   rc = gethostname (my.host, &x_len);
   if (rc < 0)  strcpy (my.host, "unknown");
   RPTG_FULL   printf ("   host       : %s\n", my.host);
   /*---(get the date)-------------------*/
   time_date = time (NULL);
   curr_time = localtime (&time_date);
   strftime (t, LEN_TITLE, "%y.%m.%d.%H.%M.%S.%u.%W.%j", curr_time);
   RPTG_FULL   printf ("   run time   : %s\n", t);
   RPTG_FULL   printf ("   pid        : %d\n", getpid());
   /*---(legend)-------------------------*/
   printf ("\n");
   printf ("   characteristic legend...\n");
   printf ("   act   A) add          u) update/fix   x) delete       -) none\n");
   printf ("   imp   a) absolute     n) need         v) value        c) crave        g) good         l) like         i) idea         -) none\n");
   printf ("   sys   -) all          s) server       p) programmer   e) end-user\n");
   /*---(walk lines)---------------------*/
   while (1) {
      /*---(read record)-----------------*/
      rc = CONF__read (x_recd);
      DEBUG_CONF   yLOG_value   ("read"      , rc);
      if (rc == 0) {
         DEBUG_CONF   yLOG_note    ("end of file");
         break;
      }
      if (rc < 0) {
         DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(parse the data)--------------*/
      rc = CONF__parse (BEG_PARSE, x_recd);
      DEBUG_CONF   yLOG_value   ("parse"     , rc);
      if (rc < 0) {
         CONF__unfocus ();
         DEBUG_CONF   yLOG_note    ("bad record");
         continue;
      }
      /*---(check area)------------------*/
      if (my.abbr == TYPE_AREA) {
         if (n > 0) RPTG_summary (NULL, n + 1, x_pass, x_fail, x_badd, x_modd);
         CONF__focus (my.abbr, my.desc);
         if (strchr (FOCUS_SHOWS, s_focus) != NULL) {
            printf ("\n\n\n");
            x_len = 157 - strlen (my.desc);
            printf ("AREA ========= %s %*.*s =\n", my.desc, x_len, x_len, YSTR_EQUAL);
            ++s_area;
         }
         s_step += n + 1;
         s_pass += x_pass;
         s_fail += x_fail;
         s_badd += x_badd;
         s_modd += x_modd;
         x_pass = x_fail = x_badd = x_modd = 0;
         n = -1;
         continue;
      }
      if (my.abbr == TYPE_END) {
         if (n > 0) RPTG_summary (NULL, n + 1, x_pass, x_fail, x_badd, x_modd);
         printf ("\n\n\n");
         RPTG_final (NULL, s_area, s_step, s_pass, s_fail, s_badd, s_modd);
         continue;
      }
      if (s_focus == FOCUS_NOT)   continue;
      /*---(accept)----------------------*/
      ++n;
      if (n % 5 == 0)  RPTG_divider (NULL);
      printf ("   %-10.10s  %-39.39s   %c   %c   %c   %-39.39s     ", my.verb, my.desc, my.act, my.imp, my.mach, my.target);
      /*> ystrldchg (x_recd, '', '�', LEN_RECD);                                     <* 
       *> printf ("�%.112s�", x_recd);                                                <*/
      if (my.run_mode == RUN_VERIFY) {
         if (my.color == 'y') {
            RPTG_fancify (g_check);
            printf ("%s\n", g_fancy);
         } else printf ("%s\n", g_check);
         continue;
      }
      /*---(call handler)----------------*/
      switch (my.abbr) {
      case TYPE_DIR   :
         rc = CHECK_dir   (1, my.target, my.own, my.grp, my.perms);
         rc = SET_driver  ();
         rc = CHECK_dir   (2, my.target, my.own, my.grp, my.perms);
         if (my.color == 'y') {
            RPTG_fancify (g_check);
            printf ("%s\n", g_fancy);
         } else printf ("%s\n", g_check);
         break;
      case TYPE_FILE  :
         rc = CHECK_file  (1, my.target, my.own, my.grp, my.perms);
         rc = SET_driver  ();
         rc = CHECK_file  (2, my.target, my.own, my.grp, my.perms);
         if (my.color == 'y') {
            RPTG_fancify (g_check);
            printf ("%s\n", g_fancy);
         } else printf ("%s\n", g_check);
         break;
      case TYPE_SYM   :
         rc = CHECK_sym   (1, my.target, my.type, my.source);
         rc = SET_driver  ();
         rc = CHECK_sym   (2, my.target, my.type, my.source);
         if (my.color == 'y') {
            RPTG_fancify (g_check);
            printf ("%s\n", g_fancy);
         } else printf ("%s\n", g_check);
         break;
      case TYPE_BLOCK :
         rc = CHECK_block (1, my.target, my.own, my.grp, my.perms, my.source);
         rc = SET_driver  ();
         rc = CHECK_block (2, my.target, my.own, my.grp, my.perms, my.source);
         if (my.color == 'y') {
            RPTG_fancify (g_check);
            printf ("%s\n", g_fancy);
         } else printf ("%s\n", g_check);
         break;
      case TYPE_CHAR  :
         rc = CHECK_char  (1, my.target, my.own, my.grp, my.perms, my.source);
         rc = SET_driver  ();
         rc = CHECK_char  (2, my.target, my.own, my.grp, my.perms, my.source);
         if (my.color == 'y') {
            RPTG_fancify (g_check);
            printf ("%s\n", g_fancy);
         } else printf ("%s\n", g_check);
         break;
      default         :
         printf ("   �---request---   ---checks---   ---update---   --rechecks--   J�\n");
         break;
      }
      /*---(counts)----------------------*/
      switch (g_check [END_FINAL]) {
      case 'Y' :  ++x_pass;     break;
      case '-' :  ++x_fail;     break;
      default  :  ++x_badd;     break;
      }
      if (strncmp (g_check + BEG_UPDATE, "���������� y", 12) == 0)  ++x_modd;

#define     BEG_UPDATE    30
      /*---(done)------------------------*/
   }
   /*---(close file)---------------------*/
   rc = CONF__close ();
   DEBUG_CONF   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_CONF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_CONF   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    unit testing accessor                     ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char*            /* [------] unit test accessor ------------------------------*/
CONF__unit              (char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [LEN_HUND]  = "";
   char        s           [LEN_HUND]  = "";
   /*---(prepare)------------------------*/
   ystrlcpy  (unit_answer, "CONF_unit        : question not understood", LEN_UNIT);
   /*---(fields)-------------------------*/
   if        (strncmp (a_question, "valid"          , 20)   == 0) {
      snprintf (unit_answer, LEN_UNIT, "CONF valid  (%2d) : %3d�%s�"  , s_nverb, strlen (s_valid), s_valid   );
   } else if (strncmp (a_question, "what"           , 20)   == 0) {
      sprintf (t, "%2d�%.40s�", strlen (my.desc), my.desc);
      snprintf (unit_answer, LEN_UNIT, "CONF what        : %c %-5.5s  %-44.44s  %c  %c  %c", my.abbr, my.verb, t, my.act, my.imp, my.mach);
   } else if (strncmp (a_question, "whom"           , 20)   == 0) {
      sprintf (t, "%2d�%.40s�", strlen (my.target), my.target);
      sprintf (s, "%2d�%.40s�", strlen (my.source), my.source);
      snprintf (unit_answer, LEN_UNIT, "CONF whom        : %-44.44s  %-10.10s  %-10.10s  %-10.10s  %c %s", t, my.own, my.grp, my.perms, my.type, s);
      /*> } else if (strncmp (a_question, "desc"           , 20)   == 0) {                                                   <* 
       *>    snprintf (unit_answer, LEN_UNIT, "CONF_desc        : %3d:%.35s"     , strlen (my.desc      ), my.desc      );   <*/
      /*> } else if (strncmp (a_question, "mach"           , 20)   == 0) {                                                   <* 
       *>    snprintf (unit_answer, LEN_UNIT, "CONF_machine     : %3d:%.35s"     , strlen (my.mach      ), my.mach      );   <*/
      /*> } else if (strncmp (a_question, "target"         , 20)   == 0) {                                                   <* 
       *>    snprintf (unit_answer, LEN_UNIT, "CONF_target      : %3d:%.35s"     , strlen (my.target    ), my.target    );   <*/
      /*> } else if (strncmp (a_question, "importance"     , 20)   == 0) {                                                   <* 
       *>    snprintf (unit_answer, LEN_UNIT, "CONF_importance  : %3d:%.35s"     , strlen (my.importance), my.importance);   <*/
      /*> } else if (strncmp (a_question, "users"          , 20)   == 0) {                                                   <* 
       *>    snprintf (unit_answer, LEN_UNIT, "CONF_users       : %3d:%.35s"     , strlen (my.users     ), my.users     );   <*/
      /*> } else if (strncmp (a_question, "own"            , 20)   == 0) {                                                   <* 
       *>    snprintf (unit_answer, LEN_UNIT, "CONF_own         : %3d:%.35s"     , strlen (my.own       ), my.own       );   <*/
      /*> } else if (strncmp (a_question, "grp"            , 20)   == 0) {                                                   <* 
       *>    snprintf (unit_answer, LEN_UNIT, "CONF_grp         : %3d:%.35s"     , strlen (my.grp       ), my.grp       );   <*/
      /*> } else if (strncmp (a_question, "perms"          , 20)   == 0) {                                                   <* 
       *>    snprintf (unit_answer, LEN_UNIT, "CONF_perms       : %3d:%.35s"     , strlen (my.perms     ), my.perms     );   <*/
      /*> } else if (strncmp (a_question, "test"           , 20)   == 0) {                                                   <* 
       *>    snprintf (unit_answer, LEN_UNIT, "CONF_test        : %3d:%.35s"     , strlen (my.test      ), my.test      );   <*/
      /*> } else if (strncmp (a_question, "source"         , 20)   == 0) {                                                   <* 
       *>    snprintf (unit_answer, LEN_UNIT, "CONF_source      : %3d:%.35s"     , strlen (my.source    ), my.source    );   <*/
}
/*---(complete)-----------------------*/
return unit_answer;
}

/*============================[[ end-of-code ]]===============================*/
