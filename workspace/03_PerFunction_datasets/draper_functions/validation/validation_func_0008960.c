getCountryCode( const gchar *pnFullNumber ) {
	gchar *pnSubString = NULL;
	int nIndex;
	int nLen = strlen( pnFullNumber );

	for ( nIndex = 6; nIndex > 0; nIndex-- ) {
		if ( nLen > nIndex ) {
			pnSubString = getSubString( ( char * ) pnFullNumber, 0, nIndex );
			if ( pnSubString != NULL ) {
				if ( g_hash_table_lookup( psLookupTable, ( gpointer ) atol( pnSubString ) ) ) {
					return pnSubString;
				}
				g_free( pnSubString );
			}
		}
	}

	return NULL;
}
