addrcache_add_person( AddressCache *cache, ItemPerson *person ) {
	gboolean retVal = FALSE;

	cm_return_val_if_fail( cache != NULL, FALSE );
	cm_return_val_if_fail( person != NULL, FALSE );

	retVal = addrcache_hash_add_person( cache, person );
	if( retVal ) {
		addritem_folder_add_person( cache->rootFolder, person );
		cache->dirtyFlag = TRUE;
	}
	return retVal;
}
