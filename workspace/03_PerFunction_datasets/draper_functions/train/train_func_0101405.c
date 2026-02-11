pblock_set_dn( void *value, struct berval *dn, struct berval *ndn, void *memctx )
{
	struct berval bv;

	if ( !BER_BVISNULL( dn )) {
		slap_sl_free( dn->bv_val, memctx );
		BER_BVZERO( dn );
	}
	if ( !BER_BVISNULL( ndn )) {
		slap_sl_free( ndn->bv_val, memctx );
		BER_BVZERO( ndn );
	}

	bv.bv_val = (char *)value;
	bv.bv_len = ( value != NULL ) ? strlen( bv.bv_val ) : 0;

	return dnPrettyNormal( NULL, &bv, dn, ndn, memctx );
}
