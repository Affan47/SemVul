cmd_kick (struct session *sess, char *tbuf, char *word[], char *word_eol[])
{
	char *nick = word[2];
	char *reason = word_eol[3];
	if (*nick)
	{
		sess->server->p_kick (sess->server, sess->channel, nick, reason);
		return TRUE;
	}
	return FALSE;
}
