ACLOCAL_AMFLAGS = -I m4 --install
nodist_include_HEADERS = config.h
bin_PROGRAMS=lib_tiny_font
lib_tiny_font_SOURCES= \
	src/main.h \
	src/main.c \
	src/bdf_parser/bdf_parser.h \
	src/bdf_parser/bdf_parser.c
lib_tiny_font_CFLAGS = -std=c11
EXTRA_DIST = m4/NOTES
