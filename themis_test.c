/*============================[[    beg-code    ]]============================*/
#include    "themis.h"




/*====================------------------------------------====================*/
/*===----                   helpers for unit testing                   ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char       /*----: set up program test file locations ------------------------*/
TEST__unit_files        (void)
{
   snprintf (my.name_root   , LEN_STR, "%s"    , DIR_TEST);
   snprintf (my.name_conf   , LEN_STR, "%s%s%s", DIR_TEST , DIR_ETC  , FILE_CONF );
   snprintf (my.name_full   , LEN_STR, "%s%s%s", DIR_TEST , DIR_YHIST, FILE_FULL );
   snprintf (my.name_summ   , LEN_STR, "%s%s%s", DIR_TEST , DIR_YHIST, FILE_SUMM );
   snprintf (my.name_warn   , LEN_STR, "%s%s%s", DIR_TEST , DIR_YHIST, FILE_WARN );
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
TEST__unit_quiet        (void)
{
   char       *x_args [1]  = { "themis" };
   PROG_urgents   (1, x_args);
   PROG_startup   (1, x_args);
   /*> PROG_logger    (1, x_args);                                                    <* 
    *> PROG_init      ();                                                             <*/
   my.report_full = '-';
   my.report_summ = '-';
   my.report_warn = '-';
   /*> PROG_testfiles ();                                                             <*/
   /*> PROG_urgs      (1, x_args);                                                    <* 
    *> PROG_args      (1, x_args);                                                    <* 
    *> PROG_begin     ();                                                             <*/
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
TEST__unit_loud         (void)
{
   char       *x_args [2]  = { "themis_unit", "@@kitchen"    };
   PROG_urgents   (2, x_args);
   PROG_startup   (2, x_args);
   /*> PROG_logger    (1, x_args);                                                    <* 
    *> PROG_init      ();                                                             <*/
   my.report_full = '-';
   my.report_summ = '-';
   my.report_warn = '-';
   /*> PROG_testfiles ();                                                             <*/
   /*> PROG_urgs      (2, x_args);                                                    <* 
    *> PROG_args      (2, x_args);                                                    <* 
    *> PROG_begin     ();                                                             <*/
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
TEST__unit_end          (void)
{
   PROG_shutdown  ();
   return 0;
}

