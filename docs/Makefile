# vim: ts=8 noexpandtab
# $Id: Makefile,v 1.11 2003/10/11 04:12:43 stj2 Exp $

# Edit the below:
TEXFILES=$(wildcard *.tex)
BIBFILE=pubs.bib
TARGET=thesis

# The following should not need editing:
export TEXFILES BIBFILE TARGET

#$(TARGET).pdf: spellcheck $(TEXFILES) $(BIBFILE)
#	$(MAKE) -C images pdf
#	$(MAKE) -C work pdf

$(TARGET).ps: spellcheck $(TEXFILES) $(BIBFILE)
	$(MAKE) -C images ps
	$(MAKE) -C work ps

$(TARGET).dvi:
	$(MAKE) $(TARGET).ps

#spellcheck:
#	ispell -t $(TEXFILES)

.PHONY: read show showx clean wordcount images debug spellcheck

debug:
	$(MAKE) -C images
	$(MAKE) -C work debug

pdfdebug:
	$(MAKE) -C images pdf
	$(MAKE) -C work pdfdebug

read: $(TARGET).dvi
	evince work/$(TARGET).dvi &

gvshow: $(TARGET).ps
	gv $(TARGET).ps

pdfshow: $(TARGET).pdf
	xpdf $(TARGET).pdf

acroshow: $(TARGET).pdf
	acroread $(TARGET).pdf

dvishow: $(TARGET).dvi
	evince work/$(TARGET).dvi &

clean:
	@rm $(TARGET).pdf 2>/dev/null; true
	@rm $(TARGET).ps 2>/dev/null; true
	@rm $(TARGET).dvi 2>/dev/null; true
	@rm *~
	$(MAKE) -C work clean
	$(MAKE) -C images clean

wordcount:
	@echo Approximate word count: `grep -v '^\\\\' $(TEXFILES)|grep -v '^%'|wc -w`
