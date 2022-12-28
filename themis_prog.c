/*============================[[    beg-code    ]]============================*/
#include    "themis.h"



tACCESSOR   my;
char        unit_answer [LEN_UNIT];



/*====================------------------------------------====================*/
/*===----                   standard program functions                 ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char*        /*--: return versioning information ---------[ leaf-- [ ------ ]-*/
PROG_version       (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strlcpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strlcpy (t, "[gnu gcc    ]", 15);
#elif  __CBANG__  > 0
   strlcpy (t, "[cbang      ]", 15);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 18);
#else
   strlcpy (t, "[unknown    ]", 15);
#endif
   snprintf (my.version, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return my.version;
}



/*====================------------------------------------====================*/
/*===----                       pre-initialization                     ----===*/
/*====================------------------------------------====================*/
static void      o___PREINIT_________________o (void) {;}

char       /*----: very first setup ------------------s-----------------------*/
PROG__header            (void)
{
   /*---(header)----------------------*/
   DEBUG_PROG   yLOG_enter (__FUNCTION__);
   /*---(versioning)------------------*/
   DEBUG_PROG   yLOG_info     ("themis"  , PROG_version    ());
   DEBUG_PROG   yLOG_info     ("purpose" , P_PURPOSE);
   DEBUG_PROG   yLOG_info     ("namesake", P_NAMESAKE);
   DEBUG_PROG   yLOG_info     ("heritage", P_HERITAGE);
   DEBUG_PROG   yLOG_info     ("imagery" , P_IMAGERY);
   DEBUG_PROG   yLOG_note     ("custom core");
   DEBUG_PROG   yLOG_info     ("yURG"    , yURG_version      ());
   DEBUG_PROG   yLOG_info     ("yLOG"    , yLOGS_version     ());
   DEBUG_PROG   yLOG_info     ("ySTR"    , ySTR_version      ());
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit  (__FUNCTION__);
   return 0;
}

char
PROG_urgents            (int a_argc, char *a_argv [])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(set mute)-----------------------*/
   yURG_all_mute ();
   /*---(start logger)-------------------*/
   rc = yURG_logger  (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("logger"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(process urgents)----------------*/
   rc = yURG_urgs    (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("logger"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(process urgents)----------------*/
   rc = PROG__header ();
   DEBUG_PROG   yLOG_value    ("header"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   return rc;
}


/*====================------------------------------------====================*/
/*===----                      startup functions                       ----===*/
/*====================------------------------------------====================*/
static void      o___STARTUP_________________o (void) {;}

char       /*----: very first setup ------------------s-----------------------*/
PROG__init              (int a_argc, char *a_argv[])
{
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(reporting flags)----------------*/
   DEBUG_PROG   yLOG_note    ("reporting flags");
   my.report_full = 'y';
   my.report_summ = 'y';
   my.report_warn = 'y';
   my.audit_only  = '-';
   /*---(conf)---------------------------*/
   DEBUG_PROG   yLOG_note    ("configuration vars");
   my.lines       = 0;
   /*---(file pointers)------------------*/
   DEBUG_PROG   yLOG_note    ("file pointers");
   CONF_init ();
   my.file_conf   = NULL;
   my.file_full   = NULL;
   my.file_summ   = NULL;
   my.file_warn   = NULL;
   /*---(file names)---------------------*/
   DEBUG_PROG   yLOG_note    ("file names");
   snprintf (my.name_root   , LEN_STR, "%s"  , "");
   DEBUG_PROG   yLOG_info     ("root"    , my.name_root);
   snprintf (my.name_conf   , LEN_STR, "%s%s", DIR_ETC  , FILE_CONF );
   DEBUG_PROG   yLOG_info     ("conf"    , my.name_conf);
   snprintf (my.name_full   , LEN_STR, "%s%s", DIR_YHIST, FILE_FULL );
   DEBUG_PROG   yLOG_info     ("full"    , my.name_full);
   snprintf (my.name_summ   , LEN_STR, "%s%s", DIR_YHIST, FILE_SUMM );
   DEBUG_PROG   yLOG_info     ("summ"    , my.name_summ);
   snprintf (my.name_warn   , LEN_STR, "%s%s", DIR_YHIST, FILE_WARN );
   DEBUG_PROG   yLOG_info     ("warn"    , my.name_warn);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> command line arguments ----------------[ ------ [ ------ ]-*/
PROG__args          (int argc, char *argv[])
{
   /*---(locals)-------------------------*/
   int         i           = 0;
   char       *a           = NULL;
   int         x_total     = 0;
   int         x_args      = 0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(process)------------------------*/
   for (i = 1; i < argc; ++i) {
      a = argv[i];
      ++x_total;
      if (a[0] == '@')  continue;
      ++x_args;
      /*---(overall)---------------------*/
      if      (strcmp(a, "--audit"           ) == 0)   my.audit_only = 'y';
      else if (strcmp(a, "--fhs"             ) == 0)   my.audit_only = 'y';
      else                                             strlcpy (my.area, a, LEN_TERSE);
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> prepare program to run ----------------[ ------ [ ------ ]-*/
PROG__begin         (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          = 0;
   char        rce         = -10;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(open detail report)-------------*/
   my.file_full = fopen (my.name_full, "w");
   --rce;  if (my.file_full == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(open summary report)------------*/
   my.file_summ = fopen (my.name_summ, "w");
   --rce;  if (my.file_summ == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(open warning report)------------*/
   my.file_warn = fopen (my.name_warn, "w");
   --rce;  if (my.file_warn == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
PROG_startup            (int a_argc, char *a_argv [])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)----------------------*/
   yURG_stage_check (YURG_BEG);
   DEBUG_PROG  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   rc = PROG__init   (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("init"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(arguments)----------------------*/
   rc = PROG__args   (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("args"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(begin)--------------------------*/
   rc = PROG__begin  ();
   DEBUG_PROG   yLOG_value    ("begin"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG  yLOG_exit  (__FUNCTION__);
   yURG_stage_check (YURG_MID);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                      program execution                       ----===*/
/*====================------------------------------------====================*/
static void      o___EXECUTION_______________o (void) {;}

char
PROG_driver             (void)
{
}



/*====================------------------------------------====================*/
/*===----                        program shutdown                      ----===*/
/*====================------------------------------------====================*/
static void      o___SHUTDOWN________________o (void) {;}

char         /*--> shutdown program ----------------------[ ------ [ ------ ]-*/
PROG__end               (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          = 0;
   char        rce         = -10;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(close detail report)------------*/
   DEBUG_PROG   yLOG_point   ("*file_full", my.file_full);
   rc = fclose (my.file_full);
   --rce;  if (rc != 0) {
      return rce;
   }
   /*---(close summary report)-----------*/
   DEBUG_PROG   yLOG_point   ("*file_summ", my.file_summ);
   rc = fclose (my.file_summ);
   --rce;  if (rc != 0) {
      return rce;
   }
   /*---(close warning report)-----------*/
   DEBUG_PROG   yLOG_point   ("*file_warn", my.file_warn);
   rc = fclose (my.file_warn);
   --rce;  if (rc != 0) {
      return rce;
   }
   /*---(terminate logging)--------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   /*---(complete)-----------------------*/
   return 0;
}

char             /* [------] drive the program closure activities ------------*/
PROG_shutdown           (void)
{
   /*---(stage-check)--------------------*/
   yURG_stage_check (YURG_END);
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter    (__FUNCTION__);
   PROG__end ();
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit     (__FUNCTION__);
   DEBUG_PROG   yLOGS_end    ();
   return 0;
}


/*============================[[ end-of-code ]]===============================*/
