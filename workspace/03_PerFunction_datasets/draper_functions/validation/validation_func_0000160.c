ldapctl_full_attribute_array( LdapControl *ctl ) {
	char **ptrArray;
	GList *node, *def;
	GList *tmp = NULL;
	gint cnt, i;
	cm_return_val_if_fail( ctl != NULL, NULL );

	def = ctl->listCriteria;
	while (def) {
		tmp = g_list_append(tmp, g_strdup(def->data));
		def = def->next;
	}

	def = ldapctl_get_default_criteria_list();

	while (def) {
		if( g_list_find_custom(tmp, (gpointer)def->data,
				(GCompareFunc)strcmp2) == NULL) {
			tmp = g_list_append(tmp, g_strdup(def->data));
		}
		def = def->next;
	}

	node = tmp;
	cnt = g_list_length( tmp );
	ptrArray = g_new0( char *, 1 + cnt);
	i = 0;
	while( node ) {
		ptrArray[ i++ ] = node->data;

		node = g_list_next( node );
	}
	ptrArray[ i ] = NULL;
	return ptrArray;
}
