
AC_INIT([musli], [r1])
AM_INIT_AUTOMAKE([foreign])

AM_PROG_LIBTOOL       
AC_PROG_CXX

AC_PROG_MAKE_SET        

AC_CHECK_HEADER([UnitTest/UnitTest++.h])
AC_CHECK_LIB([UnitTest++], [main], [UNITTEST_LIBS="-lUnitTest++"], 
    AC_WARN("UnitTest++ not found."))
AC_SUBST(UNITTEST_LIBS)

AC_OUTPUT([Makefile])

