quickfind(const char *s)
{
	ht_text_listbox_item *item = (ht_text_listbox_item *)e_cursor;
	for (int j=0; j<2; j++) {
		int slen = strlen(s);
		char *i = NULL;
		if (item) {
			i = item->data[keycol];
			i = (i && *i) ? i+1 : i;
		}
		while (item && (compare_strn(i, s, slen)!=0)) {
			item = item->next;
			if (item) {
				i = item->data[keycol];
				i = (i && *i) ? i+1 : i;
			}
		}
		if (item) return item;
		item = first;
	}
	return NULL;
}
