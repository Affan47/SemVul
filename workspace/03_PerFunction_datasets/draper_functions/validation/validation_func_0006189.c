FuncLARGEST_MOVED_POINT_PERM (
    Obj                 self,
    Obj                 perm )
{
    UInt                sup;
    UInt2 *             ptPerm2;
    UInt4 *             ptPerm4;


    while ( TNUM_OBJ(perm) != T_PERM2 && TNUM_OBJ(perm) != T_PERM4 ) {
        perm = ErrorReturnObj(
            "LargestMovedPointPerm: <perm> must be a permutation (not a %s)",
            (Int)TNAM_OBJ(perm), 0L,
            "you can replace <perm> via 'return <perm>;'" );
    }


    if ( TNUM_OBJ(perm) == T_PERM2 ) {


        ptPerm2 = ADDR_PERM2(perm);
        for ( sup = DEG_PERM2(perm); 1 <= sup; sup-- ) {
            if ( ptPerm2[sup-1] != sup-1 )
                break;
        }

    }


    else {


        ptPerm4 = ADDR_PERM4(perm);
        for ( sup = DEG_PERM4(perm); 1 <= sup; sup-- ) {
            if ( ptPerm4[sup-1] != sup-1 )
                break;
        }

    }


    return INTOBJ_INT( sup );
}
