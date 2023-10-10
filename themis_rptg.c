/*============================[[    beg-code    ]]============================*/
#include    "themis.h"

int         s_summs     = 0;




char
RPTG_divider       (FILE *f)
{
   if (f == NULL) {
      printf  (   "   ---verb---  ---description-------------------------  act val sys  ---focus-------------------------------     ---request---   ---checks---   ---update---   --rechecks--   ·\n");
   } else {
      fprintf (f, "   ---verb---  ---description-------------------------  act val sys  ---focus-------------------------------     ---request---   ---checks---   ---update---   --rechecks--   ·\n");
   }
   return 0;
}

char
RPTG_summary       (FILE *f, int a_step, int a_pass, int a_fail, int a_badd, int a_modd)
{
   char        x_result    [LEN_TERSE] = "";
   if (a_step <= 0)  return 0;
   if (a_step == a_pass)  strcpy (x_result, "passed");
   else                   strcpy (x_result, "FAILED");
   RPTG_divider (NULL);
   if (f == NULL) {
      printf  (   "   SUMMARY            STEP = %4d   PASS = %4d   FAIL = %4d   BADD = %4d   MODD = %4d   ============================================================================ %s\n", a_step, a_pass, a_fail, a_badd, a_modd, x_result);
   } else {
      fprintf (f, "   SUMMARY            STEP = %4d   PASS = %4d   FAIL = %4d   BADD = %4d   MODD = %4d   ============================================================================ %s\n", a_step, a_pass, a_fail, a_badd, a_modd, x_result);
   }
   return 0;
}

char
RPTG_final         (FILE *f, int a_area, int a_step, int a_pass, int a_fail, int a_badd, int a_modd)
{
   char        x_result    [LEN_TERSE] = "";
   if (a_area <= 0)  return 0;
   if (a_step == a_pass)  strcpy (x_result, "passed");
   else                   strcpy (x_result, "FAILED");
   if (f == NULL) {
      printf  (   "END     AREA = %4d   STEP = %4d   PASS = %4d   FAIL = %4d   BADD = %4d   MODD = %4d   ============================================================================ %s\n", a_area, a_step, a_pass, a_fail, a_badd, a_modd, x_result);
   } else {
      fprintf (f, "END     AREA = %4d   STEP = %4d   PASS = %4d   FAIL = %4d   BADD = %4d   MODD = %4d   ============================================================================ %s\n", a_area, a_step, a_pass, a_fail, a_badd, a_modd, x_result);
   }
   return 0;
}

char
RPTG_fancify       (char a_check [LEN_HUND])
{
   int         l           =    0;
   char        t           [LEN_DESC] = "";
   ystrlcpy (g_fancy, "", LEN_RECD);
   l = strlen (a_check);
   /*> printf ("%2dl, %2dp, %2dc, %2du, %2dr, %2dj\n", l, END_PARSE, END_CHECK, END_UPDATE, END_RECHECK, END_FINAL);   <*/
   if (l > END_PARSE) {
      switch (a_check [END_PARSE]) {
      case '·'  :
         sprintf (t, "%-13.13s"    , a_check);
         break;
      case 'y'  :
         sprintf (t, "%s%-13.13s%s", FORE_GRN, a_check, FORE_OFF);
         break;
      case '!'  : case '?'  :
         sprintf (t, "%s%-13.13s%s", FORE_YEL, a_check, FORE_OFF);
         break;
      case '°'  : case 'F'  : default :
         sprintf (t, "%s%-13.13s%s", BOLD_ERR, a_check, BOLD_OFF);
         break;
      }
      ystrlcat (g_fancy, t, LEN_RECD);
   }
   if (l > BEG_CHECK) {
      sprintf (t, "%-3.3s"    , a_check + BEG_CHECK - 2);
      ystrlcat (g_fancy, t, LEN_RECD);
   }
   if (l > END_CHECK) {
      switch (a_check [END_CHECK]) {
      case '·'  :
         sprintf (t, "%-12.12s"    , a_check + BEG_CHECK + 1);
         break;
      case 'y'  :
         sprintf (t, "%s%-12.12s%s", FORE_GRN, a_check + BEG_CHECK + 1, FORE_OFF);
         break;
      case ' '  :
         if (my.act == ACT_DEL)  sprintf (t, "%s%-12.12s%s", FORE_GRN, a_check + BEG_CHECK + 1, FORE_OFF);
         else                    sprintf (t, "%s%-12.12s%s", FORE_YEL, a_check + BEG_CHECK + 1, FORE_OFF);
         break;
      case '-'  :
         sprintf (t, "%s%-12.12s%s", FORE_YEL, a_check + BEG_CHECK + 1, FORE_OFF);
         break;
      case '°'  : case '!'  : default :
         sprintf (t, "%s%-12.12s%s", BOLD_ERR, a_check + BEG_CHECK + 1, BOLD_OFF);
         break;
      }
      ystrlcat (g_fancy, t, LEN_RECD);
   }
   if (l > BEG_UPDATE) {
      sprintf (t, "%-3.3s"    , a_check + BEG_UPDATE - 2);
      ystrlcat (g_fancy, t, LEN_RECD);
   }
   if (l > END_UPDATE) {
      switch (a_check [END_UPDATE]) {
      case '·'  :
         sprintf (t, "%-12.12s"    , a_check + BEG_UPDATE + 1);
         break;
      case 'y'  :
         sprintf (t, "%s%-12.12s%s", FORE_GRN, a_check + BEG_UPDATE + 1, FORE_OFF);
         break;
      case ' '  : case '-'  :
         sprintf (t, "%s%-12.12s%s", FORE_YEL, a_check + BEG_UPDATE + 1, FORE_OFF);
         break;
      case '°'  : case '!'  : default :
         sprintf (t, "%s%-12.12s%s", BOLD_ERR, a_check + BEG_UPDATE + 1, BOLD_OFF);
         break;
      }
      ystrlcat (g_fancy, t, LEN_RECD);
   }
   if (l > BEG_RECHECK) {
      sprintf (t, "%-3.3s"    , a_check + BEG_RECHECK - 2);
      ystrlcat (g_fancy, t, LEN_RECD);
   }
   if (l > END_RECHECK) {
      switch (a_check [END_RECHECK]) {
      case '·'  :
         sprintf (t, "%-12.12s"    , a_check + BEG_RECHECK + 1);
         break;
      case 'y'  :
         sprintf (t, "%s%-12.12s%s", FORE_GRN, a_check + BEG_RECHECK + 1, FORE_OFF);
         break;
      case ' '  :
         if (my.act == ACT_DEL)  sprintf (t, "%s%-12.12s%s", FORE_GRN, a_check + BEG_CHECK + 1, FORE_OFF);
         else                    sprintf (t, "%s%-12.12s%s", FORE_YEL, a_check + BEG_CHECK + 1, FORE_OFF);
         break;
      case '-'  :
         sprintf (t, "%s%-12.12s%s", FORE_YEL, a_check + BEG_RECHECK + 1, FORE_OFF);
         break;
      case '°'  : case '!'  : default :
         sprintf (t, "%s%-12.12s%s", BOLD_ERR, a_check + BEG_RECHECK + 1, BOLD_OFF);
         break;
      }
      ystrlcat (g_fancy, t, LEN_RECD);
   }
   if (l >= END_FINAL) {
      sprintf (t, "%-3.3s"    , a_check + BEG_RECHECK - 2);
      ystrlcat (g_fancy, t, LEN_RECD);
      switch (a_check [END_FINAL]) {
      case '·'  :
         sprintf (t, "%-1.1s"    , a_check + END_FINAL);
         break;
      case 'Y'  :
         sprintf (t, "%s%-1.1s%s", FORE_GRN, a_check + END_FINAL, FORE_OFF);
         break;
      case ' '  : case '-'  :
         sprintf (t, "%s%-1.1s%s", FORE_YEL, a_check + END_FINAL, FORE_OFF);
         break;
      case '°'  : case '!'  : default :
         sprintf (t, "%s%-1.1s%s", BOLD_ERR, a_check + END_FINAL, BOLD_OFF);
         break;
      }
      ystrlcat (g_fancy, t, LEN_RECD);
   }
   return 0;
}

char         /*--> print header block --------------------[ ------ [ ------ ]-*/
RPTG_beg           (void)
{
   /*---(locals)-------------------------*/
   char        rc          = 0;
   int         x_len       = 0;
   time_t      time_date;
   tTIME      *curr_time   = NULL;
   char        x_temp      [100];
   tTSPEC      tv;
   /*---(static header)------------------*/
   RPTG_FULL   fprintf (my.file_full, "================================================================================\n");
   RPTG_FULL   fprintf (my.file_full, "\n");
   RPTG_FULL   fprintf (my.file_full, "focus        : SA, system administration\n");
   RPTG_FULL   fprintf (my.file_full, "niche        : cm, configuration management\n");
   RPTG_FULL   fprintf (my.file_full, "application  : themis-euboulos   (titaness of divine law, custom, and order)\n");
   RPTG_FULL   fprintf (my.file_full, "purpose      : enforce consistent structure, security, and configuration\n");
   RPTG_FULL   fprintf (my.file_full, "\n");
   RPTG_FULL   fprintf (my.file_full, "base_system  : gnu/linux   (powerful, ubiquitous, technical, and hackable)\n");
   RPTG_FULL   fprintf (my.file_full, "lang_name    : ansi-c      (wicked, limitless, universal, and everlasting)\n");
   RPTG_FULL   fprintf (my.file_full, "dependencies : yLOG, ySTR, yVAR\n");
   RPTG_FULL   fprintf (my.file_full, "size         : small       (~< 2,000 sloc)\n");
   RPTG_FULL   fprintf (my.file_full, "\n");
   RPTG_FULL   fprintf (my.file_full, "author       : rsheatherly\n");
   RPTG_FULL   fprintf (my.file_full, "created      : 2014-06 (based on my _environ.sh)\n");
   RPTG_FULL   fprintf (my.file_full, "priorities   : direct, simple, brief, vigorous, and lucid (h.w. fowler)\n");
   RPTG_FULL   fprintf (my.file_full, "end goal     : loose coupling, strict interfaces, maintainable, traceable\n");
   RPTG_FULL   fprintf (my.file_full, "\n");
   /*---(host name)----------------------*/
   rc = gethostname (my.host, &x_len);
   if (rc < 0)  strcpy (my.host, "unknown");
   RPTG_FULL   fprintf (my.file_full, "host         : %s\n", my.host);
   /*---(get the date)-------------------*/
   time_date = time (NULL);
   curr_time = localtime (&time_date);
   strftime (x_temp, 50, "%y.%m.%d.%H.%M.%S.%U", curr_time);
   RPTG_FULL   fprintf (my.file_full, "run time     : %s\n", x_temp);
   /*---(get milliseconds)---------------*/
   clock_gettime (CLOCK_MONOTONIC, &tv);
   my.time_beg += (llong) tv.tv_sec  * 1000;
   my.time_beg += (llong) tv.tv_nsec / 1000000;
   RPTG_FULL   fprintf (my.file_full, "beg msec     : %lld\n", my.time_beg);
   /*---(end of header)------------------*/
   RPTG_FULL   fprintf (my.file_full, "\n");
   RPTG_FULL   fprintf (my.file_full, "================================================================================\n");
   RPTG_FULL   fprintf (my.file_full, "\n");
   /*---(complete)-----------------------*/
   return 0;
}


char         /*--> report sub-heading --------------------[ ------ [ ------ ]-*/
RPTG_subhead       (
      /*----------+-----------+-----------------------------------------------*/
      char       *a_title,    /* text for report short description            */
      char       *a_desc,     /* text for report short description            */
      char        a_mode)     /* mode is verify or create/update              */
{  /*---(locals)-----------+-----------+-*/
   char        x_temp      [LEN_STR]   = "";
   /*---(defense)------------------------*/
   if (my.report_full != 'y')    return  0;
   /*---(header)-------------------------*/
   snprintf (x_temp, LEN_STR, "   >> %-12.12s : %s =====================================================================",
         (a_title == NULL) ? "((null))" : a_title,
         (a_desc  == NULL) ? "((null))" : a_desc );
   fprintf (my.file_full, "%-74.74s%5.5s=\n", x_temp, (a_mode == MODE_FORCED) ? "force" : "audit");
   /*---(complete)-----------------------*/
   return 0;
}

char
RPTG_single        (char *a_verb, char *a_desc, char a_mode, int a_checks, int a_passed, int a_updates, int a_warns, int a_errors)
{  /*---(locals)-----------+-----------+-*/
   char        x_temp      [LEN_STR]   = "";
   /*---(defense)------------------------*/
   if (my.report_summ != 'y')    return  0;
   /*---(headers and line breaks)--------*/
   if ((s_summs % 25) == 0) {
      RPTG_SUMM    fprintf (my.file_summ, "\nline  recd  ---verb---  ---desc---------------------------------  mod  result-  chks  pass  upds  warn  errs\n");
   }
   if ((s_summs %  5) == 0) {
      RPTG_SUMM    fprintf (my.file_summ, "\n");
   }
   /*---(summary report)-----------------*/
   RPTG_SUMM   fprintf (my.file_summ, "%4d  %4d  %-10.10s  %-40.40s   %c   ",
         s_summs, my.lines,
         (a_verb  == NULL) ? "((null))" : a_verb,
         (a_desc  == NULL) ? "((null))" : a_desc,
         a_mode);
   if        (a_errors  >  0) {
      RPTG_SUMM   fprintf (my.file_summ, "FAILURE  ");
   } else if (a_warns   > 0) {
      RPTG_SUMM   fprintf (my.file_summ, "WARNING  ");
   } else if (a_updates > 0) {
      RPTG_SUMM   fprintf (my.file_summ, "UPDATES  ");
   } else if (a_passed  > 0) {
      RPTG_SUMM   fprintf (my.file_summ, "success  ");
   }
   RPTG_SUMM   fprintf (my.file_summ, "%4d  %4d  %4d  %4d  %4d\n",
         a_checks, a_passed, a_updates, a_warns, a_errors);
   ++s_summs;
   /*---(exceptions)---------------------*/
   if (a_errors > 0) {
      RPTG_WARN   fprintf (my.file_warn, "FAILURE  %4d  %-10.10s  %-40.40s\n",
            my.lines,
            (a_verb  == NULL) ? "((null))" : a_verb,
            (a_desc  == NULL) ? "((null))" : a_desc);
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
RPTG_summ          (int a_checks, int a_passed, int a_updates, int a_warns, int a_errors)
{
   /*---(subtotals)----------------------*/
   my.sub_checks  += a_checks;
   my.sub_passed  += a_passed;
   my.sub_updates += a_updates;
   my.sub_warns   += a_warns;
   my.sub_errors  += a_errors;
   /*---(overall status)-----------------*/
   ++my.sub_entry;
   if        (a_errors  >  0) {
      RPTG_FULL   fprintf (my.file_full, "      ELUR [ FAILURE ]--- ");
      ++my.sub_fail;
   } else if (a_warns   > 0) {
      RPTG_FULL   fprintf (my.file_full, "      ELUR [ WARNING ]--- ");
      ++my.sub_fail;
   } else if (a_updates > 0) {
      RPTG_FULL   fprintf (my.file_full, "      ELUR [ UPDATES ]--- ");
      ++my.sub_change;
   } else if (a_passed  > 0) {
      RPTG_FULL   fprintf (my.file_full, "      ELUR [ success ]--- ");
      ++my.sub_good;
   }
   RPTG_FULL      fprintf (my.file_full, "chk (%4d) pas (%4d) upd (%4d) wrn (%4d) err (%4d)\n", a_checks, a_passed, a_updates, a_warns, a_errors);
   RPTG_FULL      fprintf (my.file_full, "\n");
   /*---(complete)-----------------------*/
   return 0;
}

char
RPTG_area           (char *a_title, char a_abbr)
{
   char        x_temp      [500]       = "";
   /*---(judgement)----------------------*/
   if        (my.sub_errors  >  0) {
      RPTG_FULL   fprintf (my.file_full, "   AERA [ FAILURE ]------ ");
      ++my.sub_fail;
   } else if (my.sub_warns   > 0) {
      RPTG_FULL   fprintf (my.file_full, "   AERA [ WARNING ]------ ");
      ++my.sub_fail;
   } else if (my.sub_updates > 0) {
      RPTG_FULL   fprintf (my.file_full, "   AERA [ UPDATES ]------ ");
      ++my.sub_change;
   } else if (my.sub_passed  > 0) {
      RPTG_FULL   fprintf (my.file_full, "   AERA [ success ]------ ");
      ++my.sub_good;
   }
   /*---(statistics)---------------------*/
   if        (my.sub_checks  >  0) {
      RPTG_FULL   fprintf (my.file_full, "chk (%4d) pas (%4d) upd (%4d) wrn (%4d) err (%4d)\n", my.sub_checks, my.sub_passed, my.sub_updates, my.sub_warns, my.sub_errors);
      RPTG_FULL   fprintf (my.file_full, "\n");
   }
   /*---(area title)---------------------*/
   if        (a_abbr == 'a') {
      sprintf (x_temp, "AREA     : %s ====================================================================================", a_title);
      RPTG_FULL   fprintf (my.file_full, "%-80.80s\n\n", x_temp);
   }
   /*---(grand totals)-------------------*/
   my.tot_areas++;
   my.tot_checks  += my.sub_checks;
   my.tot_passed  += my.sub_passed;
   my.tot_updates += my.sub_updates;
   my.tot_warns   += my.sub_warns;
   my.tot_errors  += my.sub_errors;
   /*---(reset area stats)---------------*/
   my.sub_checks   = 0;
   my.sub_passed   = 0;
   my.sub_updates  = 0;
   my.sub_warns    = 0;
   my.sub_errors   = 0;
   /*---(complete)-----------------------*/
   return 0;
}

char
RPTG_end           (void)
{
   /*---(locals)-------------------------*/
   time_t      time_date;
   tTIME      *curr_time   = NULL;
   char        x_temp      [100];
   tTSPEC      tv;
   /*---(footer)-------------------------*/
   RPTG_SUMM   fprintf (my.file_summ, "\nline  recd  ---verb---  ---desc---------------------------------  mod  result-  chks  pass  upds  warn  errs\n");
   RPTG_SUMM   fprintf (my.file_summ, "\n");
   if (my.tot_errors > 0) {
      RPTG_FULL   fprintf (my.file_full, "LLUF [ FAILURE ]--------- ");
      RPTG_SUMM   fprintf (my.file_summ, "summary [ FAILURE ] - - - ");
   } else if (my.tot_warns   > 0) {
      RPTG_FULL   fprintf (my.file_full, "LLUF [ WARNING ]--------- ");
      RPTG_SUMM   fprintf (my.file_summ, "summary [ WARNING ] - - - ");
   } else if (my.tot_updates > 0) {
      RPTG_FULL   fprintf (my.file_full, "LLUF [ UPDATES ]--------- ");
      RPTG_SUMM   fprintf (my.file_summ, "summary [ UPDATES ] - - - ");
   } else {
      RPTG_FULL   fprintf (my.file_full, "LLUF [ success ]--------- ");
      RPTG_SUMM   fprintf (my.file_summ, "summary [ success ] - - - ");
   }
   /*---(full totals)--------------------*/
   RPTG_FULL   fprintf (my.file_full, "chk (%4d) pas (%4d) upd (%4d) wrn (%4d) err (%4d)\n", my.tot_checks, my.tot_passed, my.tot_updates, my.tot_warns, my.tot_errors);
   RPTG_FULL   fprintf (my.file_full, "==========================================================================end===\n");
   /*---(summ totals)--------------------*/
   RPTG_SUMM   fprintf (my.file_summ, "- - - - - - - - - - - - - - - - - - - - - - - - - -   ");
   RPTG_SUMM   fprintf (my.file_summ, "%4d  %4d  %4d  %4d  %4d\n", my.tot_checks, my.tot_passed, my.tot_updates, my.tot_warns, my.tot_errors);
   /*---(get the date)-------------------*/
   time_date = time (NULL);
   curr_time = localtime (&time_date);
   strftime (x_temp, 50, "%y.%m.%d.%H.%M.%S.%U", curr_time);
   RPTG_FULL   fprintf (my.file_full, "end time     : %s\n", x_temp);
   /*---(get milliseconds)---------------*/
   clock_gettime (CLOCK_MONOTONIC, &tv);
   my.time_end += (llong) tv.tv_sec  * 1000;
   my.time_end += (llong) tv.tv_nsec / 1000000;
   RPTG_FULL   fprintf (my.file_full, "end msec     : %lld\n", my.time_end);
   RPTG_FULL   fprintf (my.file_full, "dur msec     : %lld\n", my.time_end - my.time_beg);
   RPTG_SUMM   fprintf (my.file_summ, "ran in %lld msec\n", my.time_end - my.time_beg);
   RPTG_FULL   fprintf (my.file_full, "==========================================================================end===\n");
   /*---(complete)-----------------------*/
   return 0;
}

