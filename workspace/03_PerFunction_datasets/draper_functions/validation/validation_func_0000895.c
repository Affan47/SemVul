gl_merge_get_record_count (const glMerge *merge)
{
	GList *p;
	glMergeRecord *record;
	gint count;

	gl_debug (DEBUG_MERGE, "START");

	count = 0;
	for ( p=merge->priv->record_list; p!=NULL; p=p->next ) {
		record = (glMergeRecord *)p->data;

		if ( record->select_flag ) count ++;
	}

	gl_debug (DEBUG_MERGE, "END");

	return count;
}
