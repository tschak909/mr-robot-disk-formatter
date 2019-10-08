	.list off
	.include "atari.inc"

	.export start

	.segment "CODE"

	;; Boot header
	.byte $00		; Boot flags
	.byte $01		; # of sectors to load
	.byte $00		; run address
	.byte $07		; " "
	.byte $00		; init address
	.byte $07		; " "

	;; Start of program code
	;; Set color, set display list, and spin.
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

	;; The boot message
dmsg:
	.byte 0,0,0,0
	.byte 0,52,40,41,51,00,41,51,00,33,0,0,0,0,0,0,0
	.byte 0,45,50,14,00,50,47,34,47,52
	.byte 0,36,41,51,43,14,0,0,0

	;; The display list
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

	.res 44 		; Padding out to 128 bytes.
