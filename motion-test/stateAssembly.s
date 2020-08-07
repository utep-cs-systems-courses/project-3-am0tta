	.arch msp430g2553
	.p2align 1,0

jt:
	.word default 		;jt[0]
	.word case1 		;jt[1]
	.word case2  		;jt[2]
	.word case3 		;jt[3]
	.word case4 		;jt[4]

	.global advance_assembly_lang
advance_assembly_lang:
	cmp #5, &state
	jhs default
	mov &state, r12
	add r12, r12 
	mov jt(r12), r0
case1:	
        call #buzzer_set_period
	mov #1, &state
	jmp end
case2:
	call #pacman
	mov #2, &state
	jmp end
case3:
	call buzzer_set_period
	mov #3, &state
	jmp end
case4:
	call #buzzer_set_period
	mov &4, &state
	jmp end
default:
	jump end
end:
	ret
