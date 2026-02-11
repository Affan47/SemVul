addrcache_add_new_folder( AddressCache *cache, ItemFolder *parent )
{
	ItemFolder *folder;
	ItemFolder *p = parent;

	cm_return_val_if_fail( cache != NULL, NULL );

	if( !p ) p = cache->rootFolder;
	folder = addritem_create_item_folder();
	addrcache_id_folder( cache, folder );
	if( addrcache_hash_add_folder( cache, folder ) ) {
		p->listFolder = g_list_append( p->listFolder, folder );
		ADDRITEM_PARENT(folder) = ADDRITEM_OBJECT(p);
		addrcache_set_dirty( cache, TRUE );
	}
	else {
		addritem_free_item_folder( folder );
		folder = NULL;
	}
	return folder;
}
