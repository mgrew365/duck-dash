			.text
; clear_screen
			xdef		_clear_screen
_clear_screen:	
			link		a6,#0
			move.l		8(a6),a0
			move.w		#8000,d0
clear_loop:
			clr.l		(a0)+
			subq.w		#1,d0
			bne			clear_loop

			unlk		a6
			rts

; plot_square
			xdef		_plot_square
			xdef		_plot_rectangle
_plot_square:
			link		a6,#0

			move.w		16(a6),-(sp)	; side
			move.w		16(a6),-(sp)	; side
			move.w		14(a6),-(sp)	; col 
			move.w 		12(a6),-(sp)	; row
			move.l 		8(a6),-(sp)		; base pointer

			jsr			_plot_rectangle
			add.l 		#12,sp

			unlk		a6
			rts
