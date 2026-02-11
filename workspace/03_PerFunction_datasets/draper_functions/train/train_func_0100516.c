gw_catalog_compare_disk_guint64 ( GtkCList *clist, const gpointer ptr1, const gpointer ptr2) {
	GWDBDisk *disk1 = NULL, *disk2 = NULL;
	guint64 nb1 = -1, nb2 = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (ptr1!=NULL) && (ptr2!=NULL) ) {
		disk1 = (GWDBDisk*)(((GtkCListRow *)ptr1)->data);
		disk2 = (GWDBDisk*)(((GtkCListRow *)ptr2)->data);

		if ( (disk1!=NULL) && (disk2!=NULL) ) {
			switch ( clist->sort_column) {
				case GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_POSITION_DEFAULT:	nb1 = gw_db_disk_get_full ( disk1);
													nb2 = gw_db_disk_get_full ( disk2);
													break;

				case GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_POSITION_DEFAULT:		nb1 = gw_db_disk_get_free ( disk1);
													nb2 = gw_db_disk_get_free ( disk2);
													break;
			}
		}
	}

	return nb1 - nb2;
}
