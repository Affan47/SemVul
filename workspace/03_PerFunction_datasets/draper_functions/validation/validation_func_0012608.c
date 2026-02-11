gfire_purple_join_chat(PurpleConnection *p_gc, GHashTable *p_table)
{
	gfire_data *gfire = NULL;
	if (!p_gc || !(gfire = (gfire_data *)p_gc->proto_data) || !p_table)
		return;

	gchar *cid_base64 = NULL;
	guint8 *cid = NULL;
	gchar *room = (gchar*)g_hash_table_lookup(p_table, "room");
	gchar *pass = (gchar*)g_hash_table_lookup(p_table, "password");
	if(!(cid_base64 = g_hash_table_lookup(p_table, "chat_id")))
	{

		purple_debug(PURPLE_DEBUG_MISC, "gfire", "Attempting to create chat room %s\n", NN(room));
		cid = g_malloc0(XFIRE_CHATID_LEN);
	}
	else
	{
		cid = purple_base64_decode(cid_base64, NULL);
	}

	gfire_chat_join(cid, room, pass, p_gc);

	g_free(cid);
}
