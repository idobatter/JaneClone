AM_CFLAGS = @THREADSAFE_FLAGS@ @DYNAMIC_EXTENSION_FLAGS@ -DSQLITE_ENABLE_FTS3 -DSQLITE_ENABLE_RTREE
ACLOCAL_AMFLAGS = -I m4

janeclonedir 		= $(pkglibdir)
janeclone_LTLIBRARIES	= libsqlite3.la
libsqlite3_la_SOURCES   = sqlite3.c
libsqlite3_la_LDFLAGS   = -no-undefined -version-info 8:6:8

janeclone_PROGRAMS 	= sqlite3
sqlite3_SOURCES 	= shell.c sqlite3.h
sqlite3_LDADD 		= $(top_builddir)/sqlite3/libsqlite3.la @READLINE_LIBS@
sqlite3_DEPENDENCIES 	= $(top_builddir)/sqlite3/libsqlite3.la

noinst_HEADERS = sqlite3.h sqlite3ext.h
