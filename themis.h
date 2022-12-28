/*============================[[ beg-of-code ]]===============================*/


/*===[[ HEADER ]]=============================================================*/
/*                      ´·········1·········2·········3·········4·········5·········6·········7*/
/*--------- 12345678901 ´123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/
/*········· ··········· ´·····························´········································*/
#define     P_NAME      "themis"
#define     P_FOCUS     "SA, system administration"
#define     P_NICHE     "cm, configuration management"
#define     P_SUBJECT   "system configuration enforcer"
#define     P_PURPOSE   "enforce consistent structure, security, and configuration"
/*········· ··········· ´·····························´········································*/
#define     P_NAMESAKE  "themis-euboulos (divine law)"
#define     P_PRONOUNCE "thee·mihs"
#define     P_HERITAGE  "titaness of divine law, custom, & order"
#define     P_BRIEFLY   "divine law, custom, & order"
#define     P_IMAGERY   ""
#define     P_REASON    ""
/*········· ··········· ´·····························´········································*/
#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT
/*········· ··········· ´·····························´········································*/
#define     P_HOMEDIR   "/home/system/themis.configuration_management"
#define     P_BASENAME  "themis"
#define     P_FULLPATH  "/usr/local/sbin/themis"
#define     P_SUFFIX    "···"
#define     P_CONTENT   "···"
/*········· ··········· ´·····························´········································*/
#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_COMPILER  "gcc 5.3.0"
#define     P_CODESIZE  "large       (appoximately 10,000 slocl)"
#define     P_DEPENDS   "none"
/*········· ··········· ´·····························´········································*/
#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2014-06"
/*········· ··········· ´·····························´········································*/
#define     P_VERMAJOR  ""
#define     P_VERMINOR  ""
#define     P_VERNUM    "2.0c"
#define     P_VERTXT    "basic entry creation in place"
/*········· ··········· ´·····························´········································*/
#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"
/*········· ··········· ´·····························´········································*/
/*--------- 12345678901 ´123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/
/*                      ´·········1·········2·········3·········4·········5·········6·········7*/
/*===[[ HEADER END ]]=========================================================*/


/*===[[ HEADER BLOCK ]]=======================================================*/
/*
 *   focus         : SA, system administration
 *   niche         : cm, configuration management
 *   heritage      : themis-euboulos (titaness of divine law, custom, & order)
 *   purpose       : enforce consistent structure, security, and configuration
 *
 *   base_system   : gnu/linux   (powerful, ubiquitous, technical, and hackable)
 *   lang_name     : ansi-c      (wicked, limitless, universal, and everlasting)
 *   dependencies  : ySTR, yLOG, yVAR
 *   size          : small       (~< 2,000 slocL)
 * 
 *   author        : heatherly
 *   created       : 2014-06
 *   priorities    : direct, simple, brief, vigorous, and lucid (h.w. fowler)
 *   end goal      : loosely coupled, strict interface, maintainable, traceable
 *
 * 
 *   0. micro       (u)   ~<        100 slocl
 *   1. tiny        (t)   ~<        500 slocl
 *   2. small       (s)   ~<      2,000 slocl
 *   3. moderate    (m)   ~<     10,000 slocl
 *   4. large       (l)   ~<     50,000 slocl
 *   5. huge        (h)   ~<    250,000 slocl
 *   6. elephantine (e)   ~<  1,000,000 slocl
 *   7. gargantuan  (g)    >  1,000,000 slocl
 */

/*===[[ REASONING ]]==========================================================*/
/*
 *
 *   problem statement (p) ---------------------------------
 *
 *   operating a single system over a moderate time-frame, multiple systems
 *   which must interoperate, or multiple consistent end-user desktops is quite
 *   challenging, very time consuming, and quite error prone.  since i desire
 *   to rebuild systems frequently, the problem is even worse as systems can be
 *   accidentally or intentionally weakened by changing permissions or
 *   configuration to inconsistent, conflicting, or more liberal settings.
 */
/*
 *   requirement and reward (rr)---------------------------
 *
 *   configuration management is the process of standardizing resource
 *   configurations, systematically handling changes, and enforcing integrity
 *   across the full infrastructure in an automated manner.  it is a very
 *   broad discipline of which i am going to only parse out the specific
 *   elements of configuration identification, status accounting, and audit/
 *   verification.  to this i will add automated update where it can be done
 *   reliably.  benefits expected are...
 *
 *      -- reduce or eliminate configuration drift by applying global standards
 *      -- reduce or eliminate non-compliance through audit and update
 *      -- reduce downtime and outages due to people and process issues
 *      -- reduce time and risk to provision a new, standard system
 *      -- enable frequent rebuilds by taking the risk out of experimentation
 *      -- enable the ability to manage large numbers of nodes in a system
 *      -- allow systems to be fixed rather than rebuilt or reimaged
 *      -- make basic configuration management a lights-out activity
 *      -- reduce risk to system security from inconsistent configuration
 *      -- run at will by making it superfast and have low system requirements
 */
/*
 *   objectives (o) ---------------------------------------
 *
 *   configuration management objectives accepted...
 *      -- keep an inventory of configuration standards for each system
 *      -- review those standards regularly to verify they are in force
 *      -- report back the findings from those audits
 *      -- alter systems to conform to the standards where feasible
 *      -- roll-out changes to standards as they are updated
 * 
 *   configuration management objectives rejected...
 *      -- not allow general purpose scripting to address additional needs
 *      -- not use ticketing system for change tracking (change control is out)
 *      -- not work on any non-heatherly systems (why would i care)
 *      -- not maintain anything other than gentoo-linux systems (enough said)
 *      -- not alter users or groups on a system (user management is separate)
 *      -- not update software versions (package management is separate)
 *      -- not inventory system components (system inventory is separate)
 *
 *   above all, it is all about...
 *      -- learning the key niches in computer and system work
 *      -- expanding my knowledge base in useful ways
 *      -- becoming a more masterful and stronger system programmer
 * 
 *   as always, applications running on my systems must...
 *      -- forgo sloppy, kitchen-sink languages, like python, java, or perl
 *      -- stay focused, small, tight, reliable, and secure
 *      -- only use human maintainable, 7-bit safe, ascii input/output files
 *      -- have dedicated, maintained, automated unit testing
 *      -- provide either detailed reporting or logging for debugging
 *      -- use secure communications between systems where required
 *      -- clean, clean code so i can maintain after long absences
 *
 *   finally, there are some very practical objectives to address...
 *      -- verify, create, and/or change directory existance and permissions
 *      -- verify, create, and/or change file existance and permissions
 *      -- verify, create, and/or change file linking to master copies
 *      -- verify, create, and/or update configuration files to latest versions
 *      -- verify, create, and/or update user specific directory structures
 */
/*
 *   alternatives (a) -------------------------------------
 *
 *   there are four main camps of software i could use for configuration
 *   managements on my systems.
 *
 *   1) top-rated, commercial-grade packages
 *      -- bcfg2    : python, developed at the argonne national laboratory
 *      -- puppet   : ruby, 
 *      -- cfengine : c, 
 *      -- chef     : ruby,
 *
 *   2) open-source alternative packages
 *
 *   3) custom integration of multiple existing tools
 *
 *   4) custom built software
 */
/*
 *   consequences (c) -------------------------------------
 *
 *   1) top-rated, commercial-grade packages
 *      ++ full capabilities built in
 *      ++ learn a system that would likely be used on the job
 *      ++ few basic execution headaches
 *      -- way over-built and huge
 *      -- no access to source code to learn (or too much to learn from)
 *      -- would only be a user and never learn to do it
 *      -- require interpretive languages and tons of libraries
 *
 *   2) open-source alternative packages
 *      ++ full capabilities built in
 *      ++ few basic execution headaches
 *      ++ supported and maintained
 *      -- way over-built and huge
 *      -- no access to source code to learn (or too much to learn from)
 *      -- would only be a user and never learn to do it
 *      -- more libraries, harnesses, and support software
 *
 *   3) smaller open-source tools
 *      ++ smaller size applications
 *      ++ learn a great deal more by integrating
 *      -- have to piece it together and integrate myself
 *      -- version inconsistency issues between tools
 *      -- much harder to maintain
 *
 *   4) custom
 *      ++ learn the core requirements and implementation
 *      ++ further my understanding of the linux system
 *      ++ further my programming skills and learning
 *      ++ does exactly what i want
 *      -- no automatic access to the latest best practices and thinking
 *      -- much more work
 */
/*
 *   trade-offs and decision (td)--------------------------
 *
 *   this is a very important systems niche and one i will have to grapple with
 *   personnally as well as expand to robotics and electronics.  that, though,
 *   still leaves all four options open if the niche is nicely covered.  but,
 *   a system administrator focuses on learning the latest commercial
 *   applications and concepts in order to compete for jobs.  i will never
 *   be abble to complete with those folks or stand the work they do.
 *
 *   so, since the packaged applications are over-built and written in
 *   interpretive, fat, hoggish interpretive languages prone to version and
 *   library hell, they are out.
 *
 *   this is too important to take lightly and an area that i will have to
 *   master to keep my vision alive.  custom it is.
 */
/*
 *   epilogue ---------------------------------------------
 *
 *   so, as always, there are many, stable, accepted, existing programs and
 *   utilities written by better programmers which are likely superior in
 *   speed, size, capability, and reliability; BUT, i would not have learned
 *   nearly as much just using them, so i follow the adage..
 *
 *   i don't want to just use the system, i want to *own* it; so that means
 *   i have to fundmentally understand the critical services which only tearing
 *   down and rebuilding can really teach -- even if its more basic in the end.
 *
 *   TO TRULY LEARN> do not seek to follow in the footsteps of the men of old;
 *   seek what they sought ~ Matsuo Basho
 *
 */

/*===[[ SECURITY ]]===========================================================*/
/*
 *   never allow applications to alter the path to configuration or output files
 *   as that can allow hackers to intervien or mask issue by hiding reports.
 *
 *
 */
/*============================================================================*/



/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YTHEMIS
#define YTHEMIS loaded






/*---(big standards)------------*/
#include    <yLOG.h>
#include    <yURG.h>
#include    <ySTR.h>
#include    <yVAR.h>

#include    <stdio.h>             /* printf, scanf                            */
#include    <stdlib.h>            /* exit()                                   */
#include    <string.h>            /* strcat, strcpy, strlen, ...              */
#include    <errno.h>             /* allow use of errno value                 */

#include    <sys/types.h>
#include    <sys/stat.h>
#include    <pwd.h>               /* getpwuid, getpwnam                       */
#include    <grp.h>               /* getgruid, getgrnam                       */
#include    <fcntl.h>             /* creat, open, fcntl                       */
#include    <unistd.h>            /* chdir, chmod, chown, getpid, symlink, ...*/
#include    <time.h>              /* time, localtime                          */
#include    <sys/sysmacros.h>

#include    <yCOLOR_solo.h>

/*---(convienence typedefs)-------------------------------------*/
typedef long   long      llong;
typedef const  int       cint;
typedef const  long      clong;
typedef const  char      cchar;

typedef struct FILE      tFILE;
typedef struct stat      tSTAT;
typedef struct tm        tTIME;
typedef struct dirent    tDIRENT;
typedef struct timespec  tTSPEC;
typedef struct passwd    tPASSWD;
typedef struct group     tGROUP;


/*> #define     STAT_NOISY        'y'                                                 <* 
 *> #define     STAT_QUIET        '-'                                                 <*/


/*===[[ DEBUGGING SETUP ]]====================================================*/
/* this is my latest standard format, vars, and urgents                       */
/* v3.0b : added signal handling                                (2014-feb-01) */
/*> struct cDEBUG                                                                      <* 
 *> {                                                                                  <* 
 *>    /+---(handle)-------------------------+/                                        <* 
 *>    int         logger;                 /+ log file so that we don't close it  +/   <* 
 *>    /+---(overall)------------------------+/  /+ abcdefghi_kl__opq_stu__x__    +/   <* 
 *>    /+ f = full urgents turns on all standard urgents                          +/   <* 
 *>    /+ k = kitchen sink and turns everything, i mean everything on             +/   <* 
 *>    /+ q = quiet turns all urgents off including the log itself                +/   <* 
 *>    char        tops;                   /+ t) broad structure and context      +/   <* 
 *>    char        summ;                   /+ s) statistics and analytical output +/   <* 
 *>    /+---(startup/shutdown)---------------+/                                        <* 
 *>    char        args;                   /+ a) command line args and urgents    +/   <* 
 *>    char        conf;                   /+ c) configuration handling           +/   <* 
 *>    char        prog;                   /+ p) program setup and teardown       +/   <* 
 *>    /+---(file processing)----------------+/                                        <* 
 *>    char        inpt;                   /+ i) text/data file input             +/   <* 
 *>    char        inpt_mas;               /+ I) text/data file input   (mas/more)+/   <* 
 *>    char        outp;                   /+ o) text/data file output            +/   <* 
 *>    char        outp_mas;               /+ O) text/data file output  (mas/more)+/   <* 
 *>    /+---(event handling)-----------------+/                                        <* 
 *>    char        loop;                   /+ l) main program event loop          +/   <* 
 *>    char        loop_mas;               /+ L) main program event loop (mas/more+/   <* 
 *>    char        user;                   /+ u) user input and handling          +/   <* 
 *>    char        apis;                   /+ z) interprocess communication       +/   <* 
 *>    char        sign;                   /+ x) os signal handling               +/   <* 
 *>    char        scrp;                   /+ b) scripts and batch operations     +/   <* 
 *>    char        hist;                   /+ h) history, undo, redo              +/   <* 
 *>    /+---(program)------------------------+/                                        <* 
 *>    char        graf;                   /+ g) grahpics, drawing, and display   +/   <* 
 *>    char        data;                   /+ d) complex data structure handling  +/   <* 
 *>    char        envi;                   /+ e) environment/filesystem           +/   <* 
 *>    char        envi_mas;               /+ E) environment/filesystem (mas/more)+/   <* 
 *>    /+---(specific)-----------------------+/                                        <* 
 *> };                                                                                 <* 
 *> typedef     struct      cDEBUG      tDEBUG;                                        <* 
 *> extern      tDEBUG      debug;                                                     <*/

/*> #define     DEBUG_TOPS          if (debug.tops      == 'y')                       <* 
 *> #define     DEBUG_SUMM          if (debug.summ      == 'y')                       <* 
 *> #define     DEBUG_ARGS          if (debug.args      == 'y')                       <* 
 *> #define     DEBUG_CONF          if (debug.conf      == 'y')                       <* 
 *> #define     DEBUG_PROG          if (debug.prog      == 'y')                       <* 
 *> #define     DEBUG_INPT          if (debug.inpt      == 'y')                       <* 
 *> #define     DEBUG_INPTM         if (debug.inpt_mas  == 'y')                       <* 
 *> #define     DEBUG_OUTP          if (debug.outp      == 'y')                       <* 
 *> #define     DEBUG_OUTPM         if (debug.outp_mas  == 'y')                       <* 
 *> #define     DEBUG_LOOP          if (debug.loop      == 'y')                       <* 
 *> #define     DEBUG_LOOPM         if (debug.loop_mas  == 'y')                       <* 
 *> #define     DEBUG_USER          if (debug.user      == 'y')                       <* 
 *> #define     DEBUG_APIS          if (debug.apis      == 'y')                       <* 
 *> #define     DEBUG_SIGN          if (debug.sign      == 'y')                       <* 
 *> #define     DEBUG_SCRP          if (debug.scrp      == 'y')                       <* 
 *> #define     DEBUG_HIST          if (debug.hist      == 'y')                       <* 
 *> #define     DEBUG_GRAF          if (debug.graf      == 'y')                       <* 
 *> #define     DEBUG_DATA          if (debug.data      == 'y')                       <* 
 *> #define     DEBUG_ENVI          if (debug.envi      == 'y')                       <* 
 *> #define     DEBUG_ENVIM         if (debug.envi_mas  == 'y')                       <*/



/*---(directory names)--------------------------*/
#define     DIR_ETC          "/etc/"
#define     DIR_YLOG         "/var/log/yLOG/"
#define     DIR_YHIST        "/var/log/yLOG.historical/"
#define     DIR_TEST         "/tmp/"

/*---(file names)-------------------------------*/
#define     FILE_CONF        "themis.conf"
#define     FILE_FULL        "themis.full_report"
#define     FILE_SUMM        "themis.summary_report"
#define     FILE_WARN        "themis.warning_report"

#define     MODE_HAMMER      'H'
#define     MODE_FORCED      'f'
#define     MODE_UPDATE      'u'
#define     MODE_AUDIT       'a'
#define     MODE_VALUES      'v'
#define     MODE_RECHECK     'q'



#define     TYPE_AREA        'a'
#define     TYPE_BLOCK       'b'
#define     TYPE_CHAR        'c'
#define     TYPE_DIR         'd'
#define     TYPE_END         'e'
#define     TYPE_FILE        'f'
#define     TYPE_GROUP       'g'
#define     TYPE_HARD        'h'
#define     TYPE_IPSOC       'i'
#define     TYPE_MACH        'm'
#define     TYPE_PIPE        'p'
#define     TYPE_SYM         's'
#define     TYPE_USER        'u'



#define     CONF_FILE         "/etc/themis.conf"

#define     RPT_FULL          "/var/log/yLOG.historical/themis.full"
#define     RPT_SUMM          "/var/log/yLOG.historical/themis.summ"
#define     RPT_WARN          "/var/log/yLOG.historical/themis.warn"

/*---(rational limits)------------------------------------------*/
#define     LEN_NAME        20     /* max naming string                       */
#define     LEN_STR        200     /* max string                              */
#define     LEN_UNIT       200     /* max unit test return string             */
#define     LEN_RECD      2000     /* max record len                          */


struct cACCESSOR {
   /*---(overall)--------------*/
   char        version     [LEN_STR];  /* version reporting string            */
   char        host        [ 20];
   llong       time_beg;
   llong       time_end;
   char        area        [LEN_TERSE];     /* focus of current run           */
   /*---(config)---------------*/
   int         lines;                  /* configuration lines read            */
   char        recd        [LEN_RECD]; /* configuration record                */
   int         len;                    /* record length                       */
   char        abbr;                   /* verb short name                     */
   char        verb        [LEN_TERSE];/* verb                                */
   char        title       [LEN_NAME]; /* reporting title                     */
   char        desc        [LEN_DESC]; /* description                         */
   char        act;                    /* action                              */
   char        imp;                    /* importance                          */
   char        mach;                   /* machine scope                       */
   char        target      [LEN_HUND]; /* target                              */
   char        own         [LEN_TERSE];/* owner                               */
   int         e_uid;                  /* ´·· expected uid                    */
   char        grp         [LEN_TERSE];/* group                               */
   int         e_gid;                  /* ´·· expected gid                    */
   char        perms       [LEN_TERSE];/* permissions                         */
   int         e_mode;                 /* ´·· expected mode                   */
   char        type;                   /* type of source                      */
   char        source      [LEN_HUND]; /* source                              */
   int         e_major;                /* ´·· device major                    */
   int         e_minor;                /* ´·· device minor                    */
   char        reason      [LEN_HUND]; /* reason for entry (optional)         */
   tSTAT       curr_stat;              /* link to file information            */
   char        exists;                 /* file exists                         */
   /*---(working)--------------*/
   int         tot_areas;              /* number of areas processed           */
   int         tot_entry;              /* total themis entries checked        */
   int         sub_entry;              /* area themis entries checked         */
   int         tot_good;               /* total themis entries successful     */
   int         sub_good;               /* area themis entries successful      */
   int         tot_change;             /* total themis entries changed        */
   int         sub_change;             /* area themis entries changed         */
   int         tot_fail;               /* total themis entries failed         */
   int         sub_fail;               /* area themis entries failed          */
   /*---(detailed working)-----*/
   int         tot_checks;             /* total checks required               */
   int         sub_checks;             /* area checks required                */
   int         tot_passed;             /* total checks passed                 */
   int         sub_passed;             /* area checks passed                  */
   int         tot_updates;            /* total updates done                  */
   int         sub_updates;            /* area updates done                   */
   int         tot_warns;              /* total warnings found                */
   int         sub_warns;              /* area warnings found                 */
   int         tot_errors;             /* total errors found                  */
   int         sub_errors;             /* area errors found                   */
   /*---(old main stuff)-------*/
   int         fields      [20][100];  /* configuration fields parsed         */
   int         conf_machs;             /* configuration machines read         */
   /*---(file names)------------*/
   char        name_root   [LEN_STR];  /* name of root directory              */
   char        name_conf   [LEN_STR];  /* name of configuration file          */
   char        name_full   [LEN_STR];  /* name of detail report               */
   char        name_summ   [LEN_STR];  /* name of summary report              */
   char        name_warn   [LEN_STR];  /* name of exception report            */
   /*---(file handles)----------*/
   FILE       *file_conf;              /* pointer to configuration file       */
   FILE       *file_full;              /* pointer to detail report            */
   FILE       *file_summ;              /* pointer to summary report           */
   FILE       *file_warn;              /* pointer to exception report         */
   /*---(reports)--------------*/
   char        report_full;            /* write detail report                 */
   char        report_summ;            /* write summary report                */
   char        report_warn;            /* write warning/exception report      */
   char        audit_only              /* always only audit                   */
};
typedef     struct  cACCESSOR  tACCESSOR;
extern      tACCESSOR   my;

#define     FLAG_AUDIT          if (my.audit_only   == 'y')


#define     MAX_USERS       200
typedef     struct cUSERS   tUSERS;
struct cUSERS {
   char        name        [LEN_NAME];
   char        desc        [LEN_STR];
   char        type        [ 20];
};
extern      tUSERS      users [MAX_USERS];
extern      int         nusers;
extern      int         cuser;


#define     MAX_MACH        200
typedef     struct cMACH    tMACH;
struct cMACH {
   char        name        [ 20];
   char        types       [500];
};
extern      tMACH       machines [MAX_MACH];
extern      int         nmachine;


#define     MAX_VERB         20
typedef     struct cVERB    tVERB;
struct cVERB {
   char        abbr;                        /* short name        */
   char        name        [LEN_TERSE];     /* verb              */
   char        desc        [LEN_DESC];      /* description       */
   char        title       [LEN_LABEL];     /* report title      */
   char        type        [LEN_LABEL];     /* type              */
   char        perm;                        /* perm abbrev       */
   char        norm;                        /* normal handling   */
};
extern const  tVERB       g_verbs [MAX_VERB];
extern char               g_norms [LEN_LABEL];

#define     MAX_PERM         50
typedef     struct cPERM    tPERM;
struct cPERM {
   char    name  [ 20];
   char    desc  [100];
   int     value;
};
extern const  tPERM       g_perms [MAX_PERM];


/*---(check mechanism)-------------------*/
#define     BEG_PARSE      3
#define     END_PARSE     12
#define     BEG_CHECK     15
#define     END_CHECK     27
#define     BEG_UPDATE    30
#define     END_UPDATE    42
#define     BEG_RECHECK   45
#define     END_RECHECK   57
#define     END_FINAL     61
extern char  g_check     [LEN_HUND];
extern char  g_fancy     [LEN_RECD];



extern char  unit_answer [LEN_UNIT];


char     *ySTR_trim          (char *a_source, char a_mode);
#define    ySTR_NONE      'n'
#define    ySTR_HEAD      'h'
#define    ySTR_TAIL      't'
#define    ySTR_BOTH      'b'
#define    ySTR_SINGLE    's'
#define    ySTR_EVERY     'e'
#define    ySTR_MAX       'm'



extern      char        g_rcs;






#define     RPTG_FULL        if (my.report_full  == 'y')
#define     RPTG_SUMM        if (my.report_summ  == 'y')
#define     RPTG_WARN        if (my.report_warn  == 'y')



/*===[[ MAIN ]]===============================================================*/
/*> char        main               (int a_argc, char *a_argv[]);                      <*/

/*===[[ themis_prog.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(support)--------------*/
char*       PROG_version       (void);
/*---(preinit)--------------*/
char        PROG__header       (void);
char        PROG_urgents       (int  a_argc, char *a_argv[]);
/*---(startup)--------------*/
char        PROG__init         (int  a_argc, char *a_argv[]);
char        PROG__args         (int  a_argc, char *a_argv[]);
char        PROG__begin        (void);
char        PROG_startup       (int  a_argc, char *a_argv[]);
/*---(shutdown)-------------*/
char        PROG__end          (void);
char        PROG_shutdown      (void);
/*---(done)----------------*/



/*===[[ themis_test.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        TEST__unit_files   (void);
char        TEST__unit_quiet   (void);
char        TEST__unit_loud    (void);
char        TEST__unit_end     (void);
/*---(done)----------------*/



/*===[[ themis_conf.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(program)--------------*/
char        CONF_init               (void);
/*---(file)-----------------*/
char        CONF__open              (cchar a_file [LEN_PATH]);
char        CONF__close             (void);
/*---(reading)--------------*/
char        CONF__clear             (void);
char        CONF__read              (char r_recd [LEN_RECD]);
/*---(parsing)--------------*/
char        CONF__verb              (char a_pos, cchar a_verb [LEN_TERSE]);
char        CONF__parse             (char a_pos, cchar a_recd [LEN_RECD]);
/*---(driver)---------------*/
char        CONF__ready             (void);
char        CONF__focus             (char a_abbr, cchar a_desc [LEN_DESC]);
char        CONF__unfocus           (void);
char        CONF_driver             (cchar a_name [LEN_PATH]);
/*---(unittest)-------------*/
char*       CONF__unit              (char *a_question, int a_num);
/*---(done)----------------*/



/*===[[ themis_conf.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(basics)---------------*/
char        CHECK_clear             (void);
char        CHECK__name             (char a_pos, cchar a_name [LEN_HUND]);
char        CHECK__exist            (char a_pos, cchar a_name [LEN_HUND]);
char        CHECK__type             (char a_pos, char a_type);
char        CHECK__owner            (char a_pos, cchar a_owner [LEN_TERSE]);
char        CHECK__group            (char a_pos, cchar a_group [LEN_TERSE]);
char        CHECK__perms            (char a_pos, cchar a_perms [LEN_TERSE]);
char        CHECK__link             (char a_pos, char a_chk, cchar a_name [LEN_HUND], cchar a_source [LEN_HUND]);
char        CHECK__nodes            (char a_pos, cchar a_source [LEN_HUND]);
/*---(combos)---------------*/
char        CHECK__driver           (char a_abbr, char a_pass, cchar a_name [LEN_HUND], cchar a_owner [LEN_TERSE], cchar a_group [LEN_TERSE], cchar a_perms [LEN_TERSE], char a_type, cchar a_source [LEN_HUND]);
char        CHECK_file              (char a_pass, cchar a_name [LEN_HUND], cchar a_owner [LEN_TERSE], cchar a_group [LEN_TERSE], cchar a_perms [LEN_TERSE]);
char        CHECK_dir               (char a_pass, cchar a_name [LEN_HUND], cchar a_owner [LEN_TERSE], cchar a_group [LEN_TERSE], cchar a_perms [LEN_TERSE]);
char        CHECK_sym               (char a_pass, cchar a_name [LEN_HUND], char a_type, cchar a_source [LEN_HUND]);
char        CHECK_char              (char a_pass, cchar a_name [LEN_HUND], cchar a_owner [LEN_TERSE], cchar a_group [LEN_TERSE], cchar a_perms [LEN_TERSE], cchar a_source [LEN_HUND]);
char        CHECK_block             (char a_pass, cchar a_name [LEN_HUND], cchar a_owner [LEN_TERSE], cchar a_group [LEN_TERSE], cchar a_perms [LEN_TERSE], cchar a_source [LEN_HUND]);
/*---(unittest)-------------*/
char*       CHECK__unit             (char *a_question, int a_num);
/*---(done)----------------*/



char        SET__exist              (char a_pos, char a_chk);
char        SET__owner              (char a_pos, char a_chk);
char        SET__group              (char a_pos, char a_chk);
char        SET__perms              (char a_pos, char a_chk);




char        /*  == 0 (good), < 0 (hard failure), > 0 (unforced change needed) */
CHECK_beginning    (
      /*----------+-----------+-----------------------------------------------*/
      char       *a_title     ,   /* title text for reporting                 */
      char       *a_desc      ,   /* text for report short description        */
      char       *a_path      ,   /* full path including name                 */
      char        a_mode      );  /* mode is verify or create/update          */

char        /*  == 0 (good), < 0 (hard failure), > 0 (unforced change needed) */
CHECK_ending       (
      /*----------+-----------+-----------------------------------------------*/
      char        a_abbr      ,   /* object type abbriviation                 */
      char       *a_path      ,   /* full path including name                 */
      char       *a_source    ,   /* link to original file                    */
      char       *a_owner     ,   /* owner of object                          */
      char       *a_group     ,   /* group of object                          */
      char       *a_perms     ,   /* correct permissions                      */
      char        a_mode      );  /* mode is verify or create/update          */

char        CHECK_base         (
      char       *a_path,
      char       *a_source,
      char        a_type,
      char        a_mode,
      char        a_output);

char        CHECK_file_OLD     (
      char       *a_title     ,   /* text for report title                    */
      char       *a_desc      ,   /* text for report short description        */
      char        a_abbr      ,   /* object type abbreviation                 */
      char       *a_path      ,   /* full path including name                 */
      char       *a_owner     ,   /* owner of object                          */
      char       *a_group     ,   /* group of object                          */
      char       *a_perms     ,   /* correct permissions                      */
      char       *a_source    ,   /* correct permissions                      */
      char        a_mode      );  /* mode is verify or create/update          */

char        CHECK_sym_OLD      (
      char       *a_title     ,   /* text for report title                    */
      char       *a_desc      ,   /* text for report short description        */
      char        a_abbr      ,   /* object type abbreviation                 */
      char       *a_path      ,   /* full path including name                 */
      char       *a_owner     ,   /* owner of object                          */
      char       *a_group     ,   /* group of object                          */
      char       *a_perms     ,   /* correct permissions                      */
      char       *a_source    ,   /* correct permissions                      */
      char        a_mode      );  /* mode is verify or create/update          */

char        CHECK_dir_OLD      (
      char       *a_title     ,   /* text for report title                    */
      char       *a_desc      ,   /* text for report short description        */
      char        a_abbr      ,   /* object type abbreviation                 */
      char       *a_path      ,   /* full path including name                 */
      char       *a_owner     ,   /* owner of object                          */
      char       *a_group     ,   /* group of object                          */
      char       *a_perms     ,   /* correct permissions                      */
      char       *a_source    ,   /* correct permissions                      */
      char        a_mode      );  /* mode is verify or create/update          */

char        CHECK_device       (
      char       *a_title     ,   /* text for report title                    */
      char       *a_desc      ,   /* text for report short description        */
      char        a_abbr      ,   /* object type abbreviation                 */
      char       *a_path      ,   /* full path including name                 */
      char       *a_owner     ,   /* owner of object                          */
      char       *a_group     ,   /* group of object                          */
      char       *a_perms     ,   /* correct permissions                      */
      char       *a_source    ,   /* correct permissions                      */
      char        a_mode      );  /* mode is verify or create/update          */


char        SET_owner          (char *a_path, char *a_owner, char  a_mode);
char        SET_group          (char *a_path, char *a_group, char  a_mode);
char        SET_perms          (char *a_path, char  a_abbr , char *a_perms, char a_mode);
char*       SET_unit           (char *a_question, int a_num);

char        RPTG_fancify       (char a_check [LEN_HUND]);
char        RPTG_beg           (void);
char        RPTG_subhead       (char *a_title, char *a_desc, char a_mode);
char        RPTG_summ          (int a_checks, int a_passed, int a_updates, int a_warns, int a_errors);
char        RPTG_single        (char *a_verb, char *a_desc, char a_mode, int a_checks, int a_passed, int a_updates, int a_warns, int a_errors);
char        RPTG_area          (char *a_title, char a_abbr);
char        RPTG_end           (void);

#endif
/*============================[[ end-of-code ]]===============================*/
