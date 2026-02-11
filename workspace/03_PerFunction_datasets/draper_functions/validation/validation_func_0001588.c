exportldif_find_dn(
			ExportLdifCtl *ctl, const ItemPerson *person )
{
	gchar *retVal = NULL;
	const GList *node;

	node = person->listAttrib;
	while( node ) {
		UserAttribute *attrib = node->data;

		node = g_list_next( node );
		if( g_utf8_collate( attrib->name, LDIF_TAG_DN ) == 0 ) {
			retVal = g_strdup( attrib->value );
			break;
		}
	}
	return retVal;
}
