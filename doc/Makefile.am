#
# documentation
#
MAN3 = 

MAN7 = 

MAN_DOC = $(MAN1) $(MAN3) $(MAN7)

MAN_TXT = $(MAN3:%.3=%.txt)
MAN_TXT += $(MAN7:%.7=%.txt)
MAN_HTML = $(MAN_TXT:%.txt=%.html)

MAINTAINERCLEANFILES = $(MAN_DOC) $(MAN_HTML)

EXTRA_DIST = asciidoc.conf $(MAN_TXT)

if INSTALL_MAN
dist_man_MANS = $(MAN_DOC)
endif

if BUILD_DOC
EXTRA_DIST += $(MAN_HTML)

SUFFIXES=.html .txt .xml .3 .7

.txt.html:
	asciidoc -d manpage -b xhtml11 -f $(srcdir)/asciidoc.conf \
		-azmq_version=@PACKAGE_VERSION@ -o$@ $<
.txt.xml:
	asciidoc -d manpage -b docbook -f $(srcdir)/asciidoc.conf \
		-azmq_version=@PACKAGE_VERSION@ -o$@ $<
.xml.1:
	xmlto man $<
.xml.3:
	xmlto man $<
.xml.7:
	xmlto man $<
endif

dist-hook : $(MAN_DOC) $(MAN_HTML)
