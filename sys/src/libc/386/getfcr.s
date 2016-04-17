
TEXT	setfcr(SB), $4
	MOVL	p+0(FP),AX
	XORB	$0x3f,AX
	MOVW	AX, 0(SP)
	WAIT
	FLDCW	0(SP)
	MOVW	0(SP), AX
	RET

TEXT	getfcr(SB), $4
	MOVW	AX, 0(SP)
	WAIT
	FSTCW	0(SP)
	MOVW	0(SP), AX
	XORB	$0x3f,AX
	RET

TEXT	getfsr(SB), $0
	WAIT
	FSTSW	AX
	RET

TEXT	setfsr(SB), $0
	WAIT
	FCLEX
	RET
