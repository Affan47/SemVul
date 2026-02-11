outbyte(c)
int c;
{
#if C_CODE || __AS09__ + __AS386_16__ + __AS386_32__ != 1
    register char *outp;

    outp = outbufptr;
    *outp++ = c;
    outbufptr = outp;
    if (outp >= outbuftop)
	flushout();
#else

#if __AS09__
# asm
	TFR	X,D
	LDX	_outbufptr,PC
	STB	,X+
	STX	_outbufptr,PC
	CMPX	_outbuftop,PC
	LBHS	CALL.FLUSHOUT
# endasm
#endif

#if __AS386_16__
# asm
# if !__FIRST_ARG_IN_AX__
	pop	dx
	pop	ax
	dec	sp
	dec	sp
# else
#  if ARGREG != DREG
	xchg	ax,bx
#  endif
# endif
	mov	bx,[_outbufptr]
	mov	[bx],al
	inc	bx
	mov	[_outbufptr],bx
	cmp	bx,[_outbuftop]
	jae	Outbyte.Flush
# if !__FIRST_ARG_IN_AX__
	jmp	dx
# else
	ret
# endif

Outbyte.Flush:
# if !__FIRST_ARG_IN_AX__
	push	dx
# endif
	br	_flushout
# endasm
#endif

#if __AS386_32__
# asm
# if !__FIRST_ARG_IN_AX__
	mov	eax,_outbyte.c[esp]
# else
#  if ARGREG != DREG
	xchg	eax,ebx
#  endif
# endif
	mov	ecx,[_outbufptr]
	mov	[ecx],al
	inc	ecx
	mov	[_outbufptr],ecx
	cmp	ecx,[_outbuftop]
	jae	Outbyte.Flush
	ret

Outbyte.Flush:
	br	_flushout
# endasm
#endif
#endif
}
