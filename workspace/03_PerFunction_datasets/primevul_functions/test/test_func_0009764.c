inbound_user_info_start (session *sess, char *nick,
								 const message_tags_data *tags_data)
{

	inbound_set_all_away_status (sess->server, nick, 0);
}
