ACLOCAL_AMFLAGS = -I config 

SUBDIRS	= doc 

pkgconfig_DATA = src/libmot.pc

AM_CPPFLAGS = \
    -I$(top_builddir)/include \
    -I$(top_srcdir)/include

#
# Library 
#
lib_LTLIBRARIES = src/libmot.la

include_HEADERS = \
    include/mot.h \
    include/contenttypes.h

src_libmot_la_SOURCES = \
    src/util.h \
    src/mot.cpp

src_libmot_la_CPPFLAGS = 
src_libmot_la_CXXFLAGS = @LIBMOT_EXTRA_CXXFLAGS@
src_libmot_la_LIBADD =

#
# Tests
#
test_apps = \
    tests/test_header_parameters \
    tests/test_mot \
    tests/test_time \
    tests/test_transportid \
    tests/write_directory_segments \
    tests/write_header_segments

tests_test_header_parameters_SOURCES = \
    tests/test_header_parameters.cpp \
    tests/catch.hpp
tests_test_header_parameters_LDADD = src/libmot.la

tests_test_mot_SOURCES = \
    tests/test_mot.cpp \
    tests/catch.hpp
tests_test_mot_LDADD = src/libmot.la

tests_test_time_SOURCES = \
    tests/test_time.cpp \
    tests/catch.hpp
tests_test_time_LDADD = src/libmot.la

tests_test_transportid_SOURCES = \
    tests/test_transportid.cpp \
    tests/catch.hpp
tests_test_transportid_LDADD = src/libmot.la

tests_write_directory_segments_SOURCES = \
    tests/write_directory_segments.cpp 
tests_write_directory_segments_LDADD = src/libmot.la

tests_write_header_segments_SOURCES = \
    tests/write_header_segments.cpp 
tests_write_header_segments_LDADD = src/libmot.la

check_PROGRAMS = ${test_apps}

#  Run the tests
TESTS = $(test_apps)

EXTRA_DIST	= COPYING NEWS README.md INSTALL.md LICENCE AUTHORS ChangeLog TODO doc
