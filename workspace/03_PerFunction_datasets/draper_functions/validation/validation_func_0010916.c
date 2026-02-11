findVcardEntry( const gchar *pnUid ) {
	GList *psList1 = NULL;
	GList *psList2 = NULL;
	GList *psCard = NULL;
	struct sCardData *psData;
	gchar *pnCurrentUid;

	for ( psList1 = psVcardList; psList1 != NULL && psList1 -> data != NULL; psList1 = psList1 -> next ) {
		psCard = psList1 -> data;

		for ( psList2 = psCard; psList2 != NULL && psList2 -> data != NULL; psList2 = psList2 -> next ) {
			psData = psList2 -> data;

			if ( strcmp( psData -> pnHeader, "UID" ) == 0 ) {
				pnCurrentUid = psData -> pnEntry;
				if ( pnCurrentUid != NULL && !strcmp( pnCurrentUid, pnUid ) ) {
					return psCard;
				}
			}
		}
	}

	return NULL;
}
