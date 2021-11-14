	.arch msp430g2553
	.p2align 1,0

	.data
dimState:	.word 0
	
	.text
	.extern redDim75
	.extern greenDim25
	.extern redDim25
	.extern greenDim75
	.extern redDim50
	.extern greenDim50
	.global dim_sequence
dim_sequence:
	cmp #1, &dimState	; If dimState = 0
	jl case_0		; Case 0
	cmp #2, &dimState	; If dimState = 1
	jl case_1		; Case 1
	cmp #3, &dimState	; If dimState = 2
	jl case_2		; Case 2
case_0:				
	call #redDim75
	call #greenDim25
	add #1, &dimState
	jmp out
case_1:
	call #redDim25
	call #greenDim75
	add #1, &dimState
	jmp out
case_2:
	call #redDim50
	call #greenDim50
	mov #0, &dimState
	jmp out
out:
	pop r0
