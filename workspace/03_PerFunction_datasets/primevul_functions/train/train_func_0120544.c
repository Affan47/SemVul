int OGRKMLLayer::TestCapability( const char * pszCap )
{
    if( EQUAL(pszCap, OLCSequentialWrite) )
    {
        return bWriter_;
    }
    else if( EQUAL(pszCap, OLCCreateField) )
    {
        return bWriter_ && iNextKMLId_ == 0;
    }
    else if( EQUAL(pszCap,OLCFastFeatureCount) )
    {


            return FALSE;


    }

    else if (EQUAL(pszCap, OLCStringsAsUTF8))
        return TRUE;

    return FALSE;
}
