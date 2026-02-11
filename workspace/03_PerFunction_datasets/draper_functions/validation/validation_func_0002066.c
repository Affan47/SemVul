bin_filter_ava( Slapi_PBlock *pb, struct berval *bvfilter,
    Slapi_Value **bvals, int ftype, Slapi_Value **retVal )
{
    int	i;

    for ( i = 0; (bvals != NULL) && (bvals[i] != NULL); i++ ) {
        const struct berval *bv = slapi_value_get_berval(bvals[i]);
        int rc = slapi_berval_cmp(bv, bvfilter);

        switch ( ftype ) {
        case LDAP_FILTER_GE:
            if ( rc >= 0 ) {
                if(retVal) {
                    *retVal = bvals[i];
                }
                return( 0 );
            }
            break;
        case LDAP_FILTER_LE:
            if ( rc <= 0 ) {
                if(retVal) {
                    *retVal = bvals[i];
                }
                return( 0 );
            }
            break;
        case LDAP_FILTER_EQUALITY:
            if ( rc == 0 ) {
                if(retVal) {
                    *retVal = bvals[i];
                }
                return( 0 );
            }
            break;
        }
    }
    if(retVal!=NULL)
    {
        *retVal= NULL;
    }
    return( -1 );
}
