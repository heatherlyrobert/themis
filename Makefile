#================================[[ beg-code ]]================================#



#===(user defined)=========================================#
# basename of executable, header, and all code files
NAME_BASE  = themis
# additional standard and outside libraries
LIB_STD    = 
# all heatherly libraries used, debug versions whenever available
LIB_MINE   = -lySTR_debug -lyVAR_debug
# directory for production code, no trailing slash
INST_DIR   = /usr/local/sbin



#===(optional)=============================================#
# extra include directories required
INC_MINE   = 
# utilities generated, separate from main program
NAME_UTIL  = 
# libraries only for the utilities
LIB_UTIL   = 



#===(post-processing)======================================#
# create a rule for...
#install_prep       :
#remove_prep        :



#===(master template)======================================#
include /usr/local/sbin/make_program



#===(post-processing)======================================#
# create a rule for...
install_post       :

remove_post        :



#================================[[ end-code ]]================================#
#===(source start)======================================================================================================================================================#



#===[[ VARABLES ]]======================================================================================================================================================#
#
##===(current variables)=================================================================================================================================================#
#BASE    = themis
#DEBUG   = ${BASE}_debug
#UNIT    = ${BASE}_unit
#HDIR    = /home/system/themis.configuration_management
#IDIR    = /usr/local/sbin
#MDIR    = /usr/share/man/man8
#
##===(compilier variables)===============================================================================================================================================#
## must have "-x c" on gcc line so stripped files work with alternate extensions
#COMP    = gcc -c -std=gnu89 -x c -g -pg -Wall -Wextra
#INCS    = -I/usr/local/include 
#
##===(linker options)========================================================================================================================================================================#
##------   (0)-------------- (1)-------------- (2)-------------- (3)-------------- (4)-------------- (5)-------------- (6)-------------- (7)-------------- (8)-------------- (9)--------------
#LINK    = gcc
#LIBDIR  = -L/usr/local/lib
#LIBS    = ${LIBDIR}         -lySTR            -lyVAR
#LIBD    = ${LIBDIR}         -lySTR_debug      -lyVAR            -lyLOG
#LIBU    = ${LIBDIR}         -lySTR_debug      -lyVAR            -lyLOG            -lyUNIT
#
##===(file lists)============================================================================================================================================================================#
##------   (0)-------------- (1)-------------- (2)-------------- (3)-------------- (4)-------------- (5)-------------- (6)-------------- (7)-------------- (8)-------------- (9)--------------
#HEADS   = ${BASE}.h
#OBJS    = ${BASE}_main.os   ${BASE}_prog.os   ${BASE}_conf.os   ${BASE}_check.os  ${BASE}_set.os    ${BASE}_rptg.os
#OBJD    = ${BASE}_main.o    ${BASE}_prog.o    ${BASE}_conf.o    ${BASE}_check.o   ${BASE}_set.o     ${BASE}_rptg.o
#OBJU    = ${BASE}_unit.o    ${BASE}_prog.o    ${BASE}_conf.o    ${BASE}_check.o   ${BASE}_set.o     ${BASE}_rptg.o
#
##===(make variables)====================================================================================================================================================#
#COPY    = cp -f
#CLEAN   = rm -f
#PRINT   = @printf
#STRIP   = @grep -v -e " DEBUG_" -e " yLOG_" 
#
#
#
##===[[ EXECUTABLES ]]===================================================================================================================================================#
#
#all                : ${BASE} ${DEBUG} ${UNIT}
#
#${BASE}            : ${OBJD}
#	${LINK}  -o ${BASE}        ${OBJS}   ${LIBS}
#
#${DEBUG}           : ${OBJD}
#	${LINK}  -o ${DEBUG}       ${OBJD}   ${LIBD}
#
#${UNIT}            : ${OBJU}
#	${LINK}  -o ${UNIT}        ${OBJU}   ${LIBU}
#
#
#
##===[[ OBJECT FILES ]]==================================================================================================================================================#
#
#${BASE}_main.o     : ${HEADS}       ${BASE}_main.c
#	${COMP}    ${BASE}_main.c                           ${INC}
#	${STRIP}   ${BASE}_main.c      > ${BASE}_main.cs
#	${COMP}    ${BASE}_main.cs    -o ${BASE}_main.os    ${INC}
#
#${BASE}_prog.o     : ${HEADS}       ${BASE}_prog.c
#	${COMP}    ${BASE}_prog.c                           ${INC}
#	${STRIP}   ${BASE}_prog.c      > ${BASE}_prog.cs
#	${COMP}    ${BASE}_prog.cs    -o ${BASE}_prog.os    ${INC}
#
#${BASE}_conf.o     : ${HEADS}       ${BASE}_conf.c
#	${COMP}    ${BASE}_conf.c                           ${INC}
#	${STRIP}   ${BASE}_conf.c      > ${BASE}_conf.cs
#	${COMP}    ${BASE}_conf.cs    -o ${BASE}_conf.os    ${INC}
#
#${BASE}_check.o    : ${HEADS}       ${BASE}_check.c
#	${COMP}    ${BASE}_check.c                          ${INC}
#	${STRIP}   ${BASE}_check.c     > ${BASE}_check.cs
#	${COMP}    ${BASE}_check.cs   -o ${BASE}_check.os   ${INC}
#
#${BASE}_set.o      : ${HEADS}       ${BASE}_set.c
#	${COMP}    ${BASE}_set.c                            ${INC}
#	${STRIP}   ${BASE}_set.c       > ${BASE}_set.cs
#	${COMP}    ${BASE}_set.cs     -o ${BASE}_set.os     ${INC}
#
#${BASE}_rptg.o     : ${HEADS}       ${BASE}_rptg.c
#	${COMP}    ${BASE}_rptg.c                           ${INC}
#	${STRIP}   ${BASE}_rptg.c      > ${BASE}_rptg.cs
#	${COMP}    ${BASE}_rptg.cs    -o ${BASE}_rptg.os    ${INC}
#
#${BASE}_unit.o     : ${BASE}.unit
#	koios    ${BASE}
##	${COMP}  -x c ${BASE}_unit.code
##	mv ${BASE}_unit.code ${BASE}_unit.c
#	${COMP}  ${BASE}_unit.c
#
#
#
##===[[ SCRIPTS ]]=======================================================================================================================================================#
#
#clean              :
#	#---(all versions)--------------------#
#	${CLEAN} ${BASE}
#	${CLEAN} ${DEBUG}
#	${CLEAN} ${UNIT}
#	#---(object and stripped files)-------#
#	${CLEAN} ${BASE}*.o
#	${CLEAN} ${BASE}*.cs
#	${CLEAN} ${BASE}*.os
#	${CLEAN} ${BASE}*.Sc
#	${CLEAN} ${BASE}*.So
#	#---(created unit code)---------------#
#	${CLEAN} ${UNIT}.code
#	${CLEAN} ${UNIT}.c
#	#---(junk files)----------------------#
#	${CLEAN} *~
#	${CLEAN} temp*
#
#bigclean           :
#	${CLEAN} .*.swp
#
#install            : ${BASE}
#	#---(production version)--------------#
#	${COPY}   ${BASE}    ${IDIR}/
#	chown     root:root  ${IDIR}/${BASE}
#	chmod     0700       ${IDIR}/${BASE}
#	@sha1sum  ${BASE}
#	#---(debug version)-------------------#
#	${COPY}  ${DEBUG}    ${IDIR}/
#	chown     root:root  ${IDIR}/${DEBUG}
#	chmod     0700       ${IDIR}/${DEBUG}
#	@sha1sum  ${DEBUG}
#	#---(man page)------------------------#
#	rm -f       ${MDIR}/${BASE}.8.bz2
#	cp -f       ${BASE}.8  ${MDIR}/
#	bzip2       ${MDIR}/${BASE}.8
#	chmod 0644  ${MDIR}/${BASE}.8.bz2
#
#remove             :
#	#---(all versions)--------------------#
#	${CLEAN}  ${IDIR}/${BASE}
#	${CLEAN}  ${IDIR}/${DEBUG}
#	#---(documentation)-------------------#
#	${CLEAN}  ${MDIR}/${BASE}.8.bz2
#
#
#
#*============================----end-of-source---============================*#
