compress( Obj        list )
{
    UInt    i, skip, len;

    skip = 0;
    i = 2;
    len = LEN_PLIST( list );
    while  ( i <= len )
    {
        while ( i<=len  &&  CELM(list, i) == 0)
        {
            skip+=2;
            i+=2;
        }
        if ( i <= len )
        {
            SET_ELM_PLIST(list, i-skip, ELM_PLIST(list, i) );
            SET_ELM_PLIST(list, i-1-skip, ELM_PLIST( list, i-1 ) );
        }
        i+=2;
    }
    SET_LEN_PLIST( list, len-skip );
    CHANGED_BAG( list );
    SHRINK_PLIST( list, len-skip );
}
