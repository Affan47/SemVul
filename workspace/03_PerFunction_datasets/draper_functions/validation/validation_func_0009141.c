processData( struct sCardData *psCardData ) {
	if ( psCardData -> pnHeader != NULL && psCardData -> pnEntry != NULL ) {

		if ( strcasecmp( psCardData -> pnHeader, "BEGIN" ) == 0 ) {

			psVcard = g_list_append( NULL, psCardData );
			psVcardList = g_list_append( psVcardList, psVcard );
		} else {
			psVcard = g_list_append( psVcard, psCardData );
		}

		if ( strcasecmp( psCardData -> pnHeader, "END" ) == 0 ) {
			processCardEnd();
		} else {
			if ( strcasecmp( psCardData -> pnHeader, "FN" ) == 0 ) {

				processFullName( psCardData );
			} else if ( strcasecmp( psCardData -> pnHeader, "END" ) == 0 ) {

				processCardEnd();
			} else if ( strcasecmp( psCardData -> pnHeader, "N" ) == 0 ) {

				processFirstLastName( psCardData );
			} else if ( strcasecmp( psCardData -> pnHeader, "TEL" ) == 0 ) {

				processTelephone( psCardData );
			} else if ( strcasecmp( psCardData -> pnHeader, "ORG" ) == 0 ) {

				processOrganization( psCardData );
			} else if ( strcasecmp( psCardData -> pnHeader, "TITLE" ) == 0 ) {

				processTitle( psCardData );
			} else if ( strcasecmp( psCardData -> pnHeader, "ADR" ) == 0 ) {

				processAddress( psCardData );
			} else if ( strcasecmp( psCardData -> pnHeader, "PHOTO" ) == 0 ) {

				processPhoto( psCardData );
			} else if ( strcasecmp( psCardData -> pnHeader, "UID" ) == 0 ) {

				processUid( psCardData );
			}
		}
	}
}
