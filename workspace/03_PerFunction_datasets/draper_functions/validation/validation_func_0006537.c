maki_server_add_user (makiServer* serv, gchar const* nick)
{
	makiUser* ret;

	g_return_val_if_fail(serv != NULL, NULL);
	g_return_val_if_fail(nick != NULL, NULL);

	g_mutex_lock(serv->mutex.users);
	ret = maki_server_internal_add_user(serv, nick);
	g_mutex_unlock(serv->mutex.users);

	return ret;
}
