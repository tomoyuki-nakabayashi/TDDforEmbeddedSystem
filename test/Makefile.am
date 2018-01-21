check_LTLIBRARIES = libgtest.la libgmock.la
libgtest_la_SOURCES = $(top_srcdir)/test/googletest/googletest/src/gtest-all.cc
libgtest_la_CPPFLAGS = -I$(top_srcdir)/test/googletest/googletest/include -I$(top_srcdir)/test/googletest/googletest
libgtest_la_LDFLAGS = -pthread
libgmock_la_SOURCES = $(top_srcdir)/test/googletest/googlemock/src/gmock-all.cc
libgmock_la_CPPFLAGS = -I$(top_srcdir)/test/googletest/googlemock/include -I$(top_srcdir)/test/googletest/googlemock $(libgtest_la_CPPFLAGS)
libgmock_la_LDFLAGS = $(libgtest_la_LDFLAGS)

check_PROGRAMS = gtest
gtest_LDADD = libgtest.la
gtest_LDFLAGS = -pthread
gtest_CPPFLAGS = \
  -I$(top_srcdir)/test/googletest/googletest \
  -I$(top_srcdir)/test/googletest/googletest/include \
  -I$(top_srcdir)/test/googletest/googlemock \
  -I$(top_srcdir)/test/googletest/googlemock/include \
  -pthread \
  -I$(top_srcdir)/src

test_sources = \
  test_main.cpp 
target_sources = 
gtest_SOURCES = $(test_sources) $(target_sources)
