xmms_medialib_entry_property_set_str_source (xmms_medialib_session_t *session,
                                             xmms_medialib_entry_t entry,
                                             const gchar *property, const gchar *value,
                                             guint32 source)
{
	gboolean ret;

	g_return_val_if_fail (property, FALSE);
	g_return_val_if_fail (session, FALSE);

	if (value && !g_utf8_validate (value, -1, NULL)) {
		XMMS_DBG ("OOOOOPS! Trying to set property %s to a NON UTF-8 string (%s) I will deny that!", property, value);
		return FALSE;
	}

	if (!xmms_medialib_check_id_in_session (entry, session)) {
		XMMS_DBG ("Trying to add property to id %d "
		          "that is not yet in the medialib. Denied.", entry);

		return FALSE;
	}

	ret = xmms_sqlite_exec (session->sql,
	                        "INSERT OR REPLACE INTO Media "
	                        "(id, value, intval, key, source) VALUES "
	                        "(%d, %Q, NULL, %Q, %d)",
	                        entry, value, property, source);

	return ret;

}
