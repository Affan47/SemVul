TestCapability( const char* pszCap )
{
    if( EQUAL( pszCap, ODsCCreateLayer ) )
        return fpOut_ != NULL ;
    else if( EQUAL( pszCap, ODsCDeleteLayer ) )
        return FALSE;
    else
        return FALSE;
}
