ACLOCAL_AMFLAGS = -I config 

SUBDIRS	= doc include

pkgconfig_DATA = src/libmot.pc

AM_CPPFLAGS = \
    -I$(top_builddir)/include \
    -I$(top_srcdir)/include

#
# Library 
#
lib_LTLIBRARIES = src/libmot.la

src_libmot_la_SOURCES = \
    src/mot.cpp

src_libmot_la_CPPFLAGS = -Iinclude
src_libmot_la_CXXFLAGS = @LIBMOT_EXTRA_CXXFLAGS@
src_libmot_la_LIBADD =

#
# Tests
#
test_apps = \
    tests/test_header_parameters \
    tests/test_mot_headermode \
    tests/test_mot_directorymode \
    tests/test_time \
    tests/test_transportid \
    tests/test_example

tests_test_header_parameters_SOURCES = \
    tests/test_header_parameters.cpp 
tests_test_header_parameters_LDADD = src/libmot.la

tests_test_mot_headermode_SOURCES = \
    tests/test_mot_headermode.cpp 
tests_test_mot_headermode_LDADD = src/libmot.la

tests_test_mot_directorymode_SOURCES = \
    tests/test_mot_directorymode.cpp 
tests_test_mot_directorymode_LDADD = src/libmot.la

tests_test_time_SOURCES = \
    tests/test_time.cpp 
tests_test_time_LDADD = src/libmot.la

tests_test_transportid_SOURCES = \
    tests/test_transportid.cpp 
tests_test_transportid_LDADD = src/libmot.la

tests_test_example_SOURCES = \
    tests/test_example.cpp 
tests_test_example_LDADD = src/libmot.la

check_PROGRAMS = ${test_apps}

#  Run the test cases
TESTS = $(test_apps)
XFAIL_TESTS =

EXTRA_DIST	= COPYING NEWS README.md INSTALL.md LICENCE AUTHORS ChangeLog TODO doc
