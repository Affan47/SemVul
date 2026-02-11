Weighting_filter P2((e, x),
	register word	* e,
	word		* x
)


{


	register longword	L_result;
	register int		k, i;


	e -= 5;


	for (k = 0; k <= 39; k++) {

		L_result = 8192 >> 1;


#undef	STEP
#define	STEP( i, H )	(e[ k + i ] * H)


#ifdef	STUPID_COMPILER
		L_result += STEP(	0, 	-134 ) ;
		L_result += STEP(	1, 	-374 )  ;

		L_result += STEP(	3, 	2054 ) ;
		L_result += STEP(	4, 	5741 ) ;
		L_result += STEP(	5, 	8192 ) ;
		L_result += STEP(	6, 	5741 ) ;
		L_result += STEP(	7, 	2054 ) ;

		L_result += STEP(	9, 	-374 ) ;
		L_result += STEP(	10, 	-134 ) ;
#else
		L_result +=
		  STEP(	0, 	-134 )
		+ STEP(	1, 	-374 )

		+ STEP(	3, 	2054 )
		+ STEP(	4, 	5741 )
		+ STEP(	5, 	8192 )
		+ STEP(	6, 	5741 )
		+ STEP(	7, 	2054 )

		+ STEP(	9, 	-374 )
		+ STEP(10, 	-134 )
		;
#endif


		L_result = SASR( L_result, 13 );
		x[k] =  (  L_result < MIN_WORD ? MIN_WORD
			: (L_result > MAX_WORD ? MAX_WORD : L_result ));
	}
}
