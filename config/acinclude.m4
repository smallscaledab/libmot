dnl ##############################################################################
dnl # LIBMOT_CONFIG_LIBTOOL                                                      #
dnl # Configure libtool. Requires AC_CANONICAL_HOST                              #
dnl ##############################################################################
AC_DEFUN([LIBMOT_CONFIG_LIBTOOL],  [{
    AC_REQUIRE([AC_CANONICAL_HOST])

    # Libtool configuration for different targets
    case "${host_os}" in
        *mingw32*|*cygwin*)
            # Disable static build by default
            AC_DISABLE_STATIC
        ;;
        *)
            # Everything else with static enabled
            AC_ENABLE_STATIC
        ;;
    esac
}])

dnl ##############################################################################
dnl # LIBMOT_CHECK_DOC_BUILD                                                     #
dnl # Check whether to build documentation and install man-pages                 #
dnl ##############################################################################
AC_DEFUN([LIBMOT_CHECK_DOC_BUILD], [{
    # Allow user to disable doc build
    AC_ARG_WITH([documentation], [AS_HELP_STRING([--without-documentation],
        [disable documentation build even if asciidoc and xmlto are present [default=no]])])

    if test "x$with_documentation" = "xno"; then
        libmot_build_doc="no"
        libmot_install_man="no"
    else
        # Determine whether or not documentation should be built and installed.
        libmot_build_doc="yes"
        libmot_install_man="yes"
        # Check for asciidoc and xmlto and don't build the docs if these are not installed.
        AC_CHECK_PROG(libmot_have_asciidoc, asciidoc, yes, no)
        AC_CHECK_PROG(libmot_have_xmlto, xmlto, yes, no)
        if test "x$libmot_have_asciidoc" = "xno" -o "x$libmot_have_xmlto" = "xno"; then
            libmot_build_doc="no"
            # Tarballs built with 'make dist' ship with prebuilt documentation.
            if ! test -f doc/zmq.7; then
                libmot_install_man="no"
                AC_MSG_WARN([You are building an unreleased version of libmot and asciidoc or xmlto are not installed.])
                AC_MSG_WARN([Documentation will not be built and manual pages will not be installed.])
            fi
        fi

        # Do not install man pages if on mingw
        if test "x$libmot_on_mingw32" = "xyes"; then
            libmot_install_man="no"
        fi
    fi

    AC_MSG_CHECKING([whether to build documentation])
    AC_MSG_RESULT([$libmot_build_doc])

    AC_MSG_CHECKING([whether to install manpages])
    AC_MSG_RESULT([$libmot_install_man])

    AM_CONDITIONAL(BUILD_DOC, test "x$libmot_build_doc" = "xyes")
    AM_CONDITIONAL(INSTALL_MAN, test "x$libmot_install_man" = "xyes")
}])

dnl ##############################################################################
dnl # LIBMOT_CHECK_ENABLE_DEBUG([action-if-found], [action-if-not-found])        #
dnl # Check whether to enable debug build and set compiler flags accordingly     #
dnl ##############################################################################
AC_DEFUN([LIBMOT_CHECK_ENABLE_DEBUG], [{

    # This flag is checked also in
    AC_ARG_ENABLE([debug], [AS_HELP_STRING([--enable-debug],
        [Enable debugging information [default=no]])])

    AC_MSG_CHECKING(whether to enable debugging information)

    if test "x$enable_debug" = "xyes"; then

        # GCC, clang and ICC
        if test "x$GCC" = "xyes" -o \
                "x$libmot_cv_c_intel_compiler" = "xyes" -o \
                "x$libmot_cv_c_clang_compiler" = "xyes"; then
            CFLAGS="-g -O0 "
        elif test "x$libmot_cv_c_sun_studio_compiler" = "xyes"; then
            CFLAGS="-g0 "
        fi

        # GCC, clang and ICC
        if test "x$GXX" = "xyes" -o \
                "x$libmot_cv_cxx_intel_compiler" = "xyes" -o \
                "x$libmot_cv_cxx_clang_compiler" = "xyes"; then
            CPPFLAGS="-g -O0 "
            CXXFLAGS="-g -O0 "
        # Sun studio
        elif test "x$libmot_cv_cxx_sun_studio_compiler" = "xyes"; then
            CPPFLAGS="-g0 "
            CXXFLAGS="-g0 "
        fi

        if test "x$ZMQ_ORIG_CFLAGS" != "xnone"; then
            CFLAGS="${CFLAGS} ${ZMQ_ORIG_CFLAGS}"
        fi
        if test "x$ZMQ_ORIG_CPPFLAGS" != "xnone"; then
            CPPFLAGS="${CPPFLAGS} ${ZMQ_ORIG_CPPFLAGS}"
        fi
        if test "x$ZMQ_ORIG_CXXFLAGS" != "xnone"; then
            CXXFLAGS="${CXXFLAGS} ${ZMQ_ORIG_CXXFLAGS}"
        fi
        AC_MSG_RESULT(yes)
    else
        AC_MSG_RESULT(no)
    fi
}])
