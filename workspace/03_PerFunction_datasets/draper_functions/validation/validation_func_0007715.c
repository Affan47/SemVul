test_session_connect(gpointer data)
{
	struct test_fix *fix = data;
	struct test_session *session;
	DBusMessage *msg;

	util_session_create(fix, 1);
	session = fix->session;

	session->notify_path = g_strdup("/foo");
	session->notify =  test_session_connect_notify;
	util_session_init(session);

	msg = session_connect(session->connection, session);
	g_assert(msg != NULL);
	g_assert(dbus_message_get_type(msg) != DBUS_MESSAGE_TYPE_ERROR);

	dbus_message_unref(msg);

	return FALSE;
}
