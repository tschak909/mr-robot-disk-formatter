	.list off
	.include "atari.inc"

	.export start

	.segment "CODE"

start:	
	lda #$5A
	sta COLOR0
	lda #144
	sta COLOR4
	lda #<dlist
	sta SDLSTL
	lda #>dlist
	sta SDLSTH
loop:	jmp loop
	
	.segment "RODATA"

dmsg:
	.byte 0,0,0,0
	.byte 0,52,40,41,51,00,41,51,00,33,0,0,0,0,0,0,0
	.byte 0,45,50,14,00,50,47,34,47,52
	.byte 0,36,41,51,43,14,0,0,0
	
dlist:
	.byte $70
	.byte $70
	.byte $70
	
	.byte $70
	.byte $70
	.byte $70
	.byte $70
	.byte $70
	.byte $70
	.byte $70

	.byte $47
	.word dmsg
	.byte $07
	.byte $41
