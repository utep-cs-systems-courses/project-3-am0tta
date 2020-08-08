	.arch msp430g2553
	.p2align 1,0
jt:
	.word default 		;jt[0]
	.word case1		;jt[1]
	.word case2		;jt[2]
	.word case3 		;jt[3]
	.word case4		;jt[4]

	.global draw_figure
draw_figure:
	cmp #5, &state
	jc default
	mov &state, r12
	add r12, r12
	mov jt(r12), r0

case1:
	mov #1, &state
	jmp end

case2:
	mov #2, &state
	jmp end
case3:
	mov #3, &state
	jmp end
case4				
	mov #4, &state
	jmp end
end:
	ret
