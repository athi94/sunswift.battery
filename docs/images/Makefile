# vim: noexpandtab ts=8
# $Id: Makefile,v 1.6 2003/10/02 21:21:20 stj2 Exp $

.PHONY: pdf ps clean

PNGS=$(wildcard *.png)
DIAS=$(wildcard *.dia)
FIGS=$(wildcard *.fig)
EPSS=$(wildcard *.eps)

OUTPUT_EPS=$(PNGS:png=eps) $(DIAS:dia=eps) $(FIGS:fig=eps) $(EPSS)
OUTPUT_PDF=$(OUTPUT_EPS:eps=pdf)

pdf: $(OUTPUT_PDF)

ps: $(OUTPUT_EPS)

clean:
	rm $(OUTPUT_PDF) $(DIAS:dia=eps) $(PNGS:png=eps) 2>/dev/null; true
	rm $(FIGS:fig=eps) 2>/dev/null; true

# Bitmap images -> EPS: PNG and JPG are covered at the moment, using
# ImageMagick's 'convert' utility
%.eps: %.png
	convert $< $@

%.eps: %.jpg
	convert $< $@

# EPS -> PDF
# epstopdf is much better than ps2pdf... it preserves bounding box
%.pdf: %.eps
	epstopdf $<

# DIA -> EPS
%.eps: %.dia
	dia --nosplash -e $@ $<

# FIG -> EPS
%.eps: %.fig
	fig2dev -L eps $< $@
