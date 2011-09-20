# vim: noexpandtab ts=8
# $Id: Makefile,v 1.10 2003/10/11 12:09:37 stj2 Exp $
.PHONY: pdf ps clean

TEXS=$(foreach i,$(TEXFILES),$(addprefix ../,$i))
BIB=$(addprefix ../,$(BIBFILE))

$(TARGET).aux: $(TEXS)
	@cp -l $(TEXS) . 2>/dev/null; true
	@cp -l ../images/*.eps . 2>/dev/null; true
	latex --interaction batchmode $(TARGET)

$(TARGET).bbl: $(BIB) $(TARGET).aux
	@cp -l $(BIB) . 2>/dev/null; true
	@cp -l ../images/*.eps . 2>/dev/null; true
	bibtex -terse $(TARGET)
	latex --interaction batchmode $(TARGET)

$(TARGET).dvi: $(TEXS) $(TARGET).bbl
	@cp -l $(TEXS) . 2>/dev/null; true
	@cp -l ../images/*.eps . 2>/dev/null; true
	latex --interaction batchmode $(TARGET)

pdf: $(TARGET).dvi
	@cp -l ../images/*.pdf . 2>/dev/null; true
	pdflatex --interaction batchmode $(TARGET)
	@cp $(TARGET).pdf ..

ps: $(TARGET).dvi
	latex --interaction batchmode $(TARGET)
	dvips -q $(TARGET) -o $(TARGET).ps
	@cp $(TARGET).ps ..

debug:
	@cp -l $(TEXS) . 2>/dev/null; true
	@cp -l $(BIB) . 2>/dev/null; true
	@cp -l ../images/*.{pdf,eps} . 2>/dev/null; true
	latex $(TARGET)

pdfdebug:
	@cp -l $(TEXS) . 2>/dev/null; true
	@cp -l $(BIB) . 2>/dev/null; true
	@cp -l ../images/*.{pdf,eps} . 2>/dev/null; true
	pdflatex $(TARGET)

clean:
	rm -f *.toc *.aux *.pdf *.ps *.eps *.log *.tex *.lof *.bib *.bbl *.blg *.dvi
