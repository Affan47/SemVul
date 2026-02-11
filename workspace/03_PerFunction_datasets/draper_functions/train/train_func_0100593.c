da_tag_max_key_ghfunc(gpointer key, Tag *item, guint32 *max_key)
{
	*max_key = MAX(*max_key, item->key);
}
