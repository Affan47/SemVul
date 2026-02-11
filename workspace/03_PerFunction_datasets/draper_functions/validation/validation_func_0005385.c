plugin_db_catalog_get_db_disk ( GWDBContext *context, GWDBDiskPK ref) {
	GWDBDisk *disk = NULL;
	GNode *node = ref;


	if ( context != NULL && ref != NULL) {
		disk = gw_db_disk_dup ( node->data, &disk);
	}

	return disk;
}
