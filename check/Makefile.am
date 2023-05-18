TESTS = check_map check_vector

check_PROGRAMS = check_map check_vector

check_map_SOURCES = check_map.c $(top_builddir)/include/cutil/map.h
check_map_CFLAGS = @CHECK_CFLAGS@ -I $(top_srcdir)/include
check_map_LDADD = $(top_builddir)/src/libcutil.la @CHECK_LIBS@

check_vector_SOURCES = check_vector.c $(top_builddir)/include/cutil/vector.h
check_vector_CFLAGS = @CHECK_CFLAGS@ -I $(top_srcdir)/include
check_vector_LDADD = $(top_builddir)/src/libcutil.la @CHECK_LIBS@
