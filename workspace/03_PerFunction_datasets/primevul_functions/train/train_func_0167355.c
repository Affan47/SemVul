_gdata_service_secure_strfree (GDataSecureString str)
{
#ifdef HAVE_GNOME
	gnome_keyring_memory_free (str);
#else


	if (str != NULL) {
		memset (str, 0, strlen (str));
	}

	g_free (str);
#endif
}
