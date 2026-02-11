DiffVecFFEFFE (
    Obj                 vecL,
    Obj                 elmR )
{
    Obj                 vecD;
    Obj *               ptrD;
    FFV                 valD;
    Obj *               ptrL;
    FFV                 valL;
    UInt                len;
    UInt                i;
    FF                  fld;
    FF *                succ;
    FFV                 valR;


    fld = FLD_FFE( ELM_PLIST( vecL, 1 ) );
    if( FLD_FFE( elmR ) != fld ) {

        if( CHAR_FF( fld ) == CHAR_FF( FLD_FFE( elmR ) ) )
            return DiffListScl( vecL, elmR );

        elmR = ErrorReturnObj(
         "<vec>-<elm>: <elm> and <vec> must belong to the same finite field",
         0L, 0L, "you can replace <elm> via 'return <elm>;'" );
        return DIFF( vecL, elmR );
    }


    len = LEN_PLIST( vecL );
    vecD = NEW_PLIST( IS_MUTABLE_OBJ(vecL) ?
		      T_PLIST_FFE :T_PLIST_FFE+IMMUTABLE, len );
    SET_LEN_PLIST( vecD, len );


    succ = SUCC_FF( fld );


    valR = VAL_FFE( elmR );
    valR = NEG_FFV( valR, succ );
    ptrL = ADDR_OBJ( vecL );
    ptrD = ADDR_OBJ( vecD );
    for ( i = 1; i <= len; i++ ) {
        valL = VAL_FFE( ptrL[i] );
        valD = SUM_FFV( valL, valR, succ );
        ptrD[i] = NEW_FFE( fld, valD );
    }


    return vecD;
}
