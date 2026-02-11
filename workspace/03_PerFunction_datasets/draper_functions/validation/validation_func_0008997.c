xmlparse_deleteplayer(guint32 connectid, xmlDocPtr doc, xmlNodePtr cur)  {

	xmlChar *tmp;
	gint32 playerid = -1, id;
	(void)connectid;
	(void)doc;

	tmp = xmlGetProp(cur, (xmlChar*)"playerid");
	if(tmp)  {
		playerid = atoi((gchar*)tmp);
		g_free(tmp);
	}

	if(playerid < 0) return;

	id = get_player_slot_with_playerid(playerid);
	if(id < 0)  return;


	game_delete_player(id);
	game_buildplayerlist();
}
