static void SCDefaultInterpolation(SplineChar *sc) {
    SplineSet *cur;
    SplinePoint *sp;


    if ( sc->ttf_instrs_len!=0 ) {
	for ( cur=sc->layers[ly_fore].splines; cur!=NULL; cur=cur->next ) {
	    for ( sp=cur->first; ; ) {
		if ( sp->ttfindex!=0xffff && SPInterpolate(sp))
		    sp->dontinterpolate = true;
		if ( sp->next==NULL )
	    break;
		sp=sp->next->to;
		if ( sp==cur->first )
	    break;
	    }
	}
    }
}
