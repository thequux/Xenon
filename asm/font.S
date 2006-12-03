global default_font
global font
default_font:
	incbin "../fonts/tools/ter-i12n.xff"
font_back:
	incbin "../fonts/ter-i12n.raw"
font:	dd font_back
