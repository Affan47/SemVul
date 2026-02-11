quickfind(const char *s)
{
	ht_text_listbox_item *item = first;
	int slen = strlen(s);
	while (item && (compare_strn(item->data[keycol], s, slen)!=0)) {
		item = item->next;
	}
	return item;
}
