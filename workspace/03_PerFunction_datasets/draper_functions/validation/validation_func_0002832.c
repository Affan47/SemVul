gkm_mock_C_SetPIN (CK_SESSION_HANDLE hSession, CK_UTF8CHAR_PTR pOldPin,
                   CK_ULONG ulOldLen, CK_UTF8CHAR_PTR pNewPin, CK_ULONG ulNewLen)
{
	Session *session;
	gchar *old;

	session = g_hash_table_lookup (the_sessions, GUINT_TO_POINTER (hSession));
	g_return_val_if_fail (session, CKR_SESSION_HANDLE_INVALID);

	old = g_strndup ((gchar*)pOldPin, ulOldLen);
	if (!old || !g_str_equal (old, the_pin))
		return CKR_PIN_INCORRECT;

	g_free (the_pin);
	the_pin = g_strndup ((gchar*)pNewPin, ulNewLen);
	n_the_pin = ulNewLen;
	return CKR_OK;
}
