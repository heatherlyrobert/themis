/*============================[[    beg-code    ]]============================*/
#include    "themis.h"



char
main               (int argc, char *argv[])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = 0;
   char        rc          = 0;
   char        x_mode      = '-';
   /*---(start-up)-----------------------*/
   rc = PROG_urgents (argc, argv);
   --rce;  if (rc < 0) {
      return rce;
   }
   rc = PROG_startup (argc, argv);
   --rce;  if (rc < 0) {
      return rce;
   }
   /*---(start-up)-----------------------*/
   /*> if (rc == 0)  rc = RPTG_beg    ();                                             <*/
   /*> if (rc == 0)  rc = CONF_prep   ();                                             <*/
   /*---(walk through checks)------------*/
   CONF_driver ("/etc/themis.conf");
   /*> while (1) {                                                                                                              <* 
    *>    /+---(read and parse)--------------+/                                                                                 <* 
    *>    rc = CONF_read   ();                                                                                                  <* 
    *>    if (rc < 0) break;                                                                                                    <* 
    *>    rc = CONF_parse  ();                                                                                                  <* 
    *>    if (rc < 0) continue;                                                                                                 <* 
    *>    /+---(set mode)--------------------+/                                                                                 <* 
    *>    if (my.audit_only == 'y')  x_mode = '-';                                                                              <* 
    *>    else                       x_mode = my.test [0];                                                                      <* 
    *>    /+---(run handlers)----------------+/                                                                                 <* 
    *>    switch (my.abbr) {                                                                                                    <* 
    *>    case  'a' :  RPTG_area        (my.desc, 'a');                                                                         <* 
    *>                 break;                                                                                                   <* 
    *>    case  'b' :  CHECK_device     (my.title, my.desc, my.abbr, my.target, my.own, my.grp, my.perms, my.source, x_mode);   <* 
    *>                 break;                                                                                                   <* 
    *>    case  'c' :  CHECK_device     (my.title, my.desc, my.abbr, my.target, my.own, my.grp, my.perms, my.source, x_mode);   <* 
    *>                 break;                                                                                                   <* 
    *>    case  'd' :  CHECK_dir_OLD    (my.title, my.desc, my.abbr, my.target, my.own, my.grp, my.perms, my.source, x_mode);   <* 
    *>                 break;                                                                                                   <* 
    *>    case  'e' :  RPTG_area        ("complete", 'e');                                                                      <* 
    *>                 break;                                                                                                   <* 
    *>    case  'f' :  CHECK_file_OLD   (my.title, my.desc, my.abbr, my.target, my.own, my.grp, my.perms, my.source, x_mode);   <* 
    *>                 break;                                                                                                   <* 
    *>    case  's' :  CHECK_sym_OLD    (my.title, my.desc, my.abbr, my.target, my.own, my.grp, my.perms, my.source, x_mode);   <* 
    *>                 break;                                                                                                   <* 
    *>    }                                                                                                                     <* 
    *>    /+---(done)------------------------+/                                                                                 <* 
    *> }                                                                                                                        <* 
    *> RPTG_end      ();                                                                                                        <*/
   /*---(shutdown)-----------------------*/
   rc = PROG_shutdown ();
   if (my.tot_errors  > 0)  return -1;
   if (my.tot_updates > 0)  return  1;
   /*---(complete)-----------------------*/
   return 0;
}



/*============================[[ end-of-code ]]===============================*/
