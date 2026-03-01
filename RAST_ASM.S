; clear_screen
			xdef		_clear_screen
_clear_screen:	
			link	a6,#0
			move.link	8(a6),a0
			move.w		#8000,d0
clear_loop:
			clr.l		(a0)+
			subq.w		#1,d0
			bne			clear_loop

			unlk		a6
			rts

;