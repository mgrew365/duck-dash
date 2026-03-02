; File: RAST_ASM.S 
; Names: Manroop Grewal, Sarah Fazal
; Instructor: Steve Kalmar
; Assignment: Checkpoint 2 - COMP 2659 
; Date Modified: March 1, 2026
; File Description: This file implements a raster graphics library in which the routines 
;                   plot images including pixels, lines, bitmaps, etc. 
;					This is done in assembly. This file only implements a couple of the routines
;					that are fully implemented in raster.c due to time constraints. 

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
			xref		_plot_rectangle
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
; plot_string
        xdef    _plot_string
        xref    _plot_character

_plot_string:
        link    a6,#0

        move.l  8(a6),a0      ; base
        move.w  12(a6),d4     ; row
        move.w  14(a6),d5     ; col
        move.l  16(a6),a1     ; ch pointer

string_loop:
        move.b  (a1),d0       ; load *ch
        beq     done          ; if zero, end string

        ; push arguments for plot_character(base, row, col, ch)
        move.w  d0,-(sp)      ; character
        move.w  d5,-(sp)      ; col
        move.w  d4,-(sp)      ; row
        move.l  a0,-(sp)      ; base

        jsr     _plot_character
        add.l   #10,sp        ; clean stack 

        addq.l  #1,a1         ; ch++
        addq.w  #8,d5         ; col += 8

        bra     string_loop

done:
        unlk    a6
        rts