AC_PREREQ(2.61)
AC_INIT([libmot], [0.0.1], [magicbadger@gmail.com])
AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE([subdir-objects foreign])
AC_CONFIG_SRCDIR([src/mot.cpp])
AC_CONFIG_HEADER([config.h])
AM_SILENT_RULES([yes])

case $host in
*linux*)
    case $target_cpu in
    x86_64)
        AC_DEFINE([__64BIT__], [], [__16BIT__, __32BIT__])
        ;;
    *)
        AC_DEFINE([__32BIT__], [], [__16BIT__, __64BIT__])
        AC_SUBST([BUILD_TARGET], ["CC='gcc -m32' CXX='g++ -m32' --target=i686"])
        flags="-m32"
    esac
    ;;
*)
    AC_DEFINE([__32BIT__], [], [__16BIT__, __64BIT__])
    AC_SUBST([GETOPT], ["xgetopt.cpp xgetopt.h"])
    AC_SUBST([WSOCK32], ["-lwsock32"])
    AC_SUBST([BUILD_HOST], ["--host i386-mingw32msvc"])
esac

CXXFLAGS="$CXXFLAGS -std=c++11"

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_INSTALL
AC_PROG_RANLIB

# Checks for header files.
AC_MSG_CHECKING([for OS type])
AC_PREPROC_IFELSE(
        [AC_LANG_SOURCE([
#ifndef _WIN32
#error windows
#endif
            ])],
        [OS=windows],
        [OS=linux]
        )
AC_MSG_RESULT([$OS])
AM_CONDITIONAL([WINDOWS], [test "x$OS" == "xwindows"])

AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([arpa/inet.h fcntl.h limits.h netdb.h netinet/in.h stddef.h stdint.h stdlib.h string.h sys/ioctl.h sys/socket.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_HEADER_TIME
AC_STRUCT_TM
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T
AC_C_VOLATILE

# Checks for library functions.
AC_PROG_GCC_TRADITIONAL
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_REALLOC
AC_TYPE_SIGNAL
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([bzero gethostbyname gettimeofday inet_ntoa memchr memmove memset socket strchr strdup strerror strrchr strstr strtol strtoul])

AM_CONDITIONAL([IS_GIT_REPO], [test -d '.git'])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 test/Makefile
                 ])
AC_OUTPUT
