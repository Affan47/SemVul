_gdata_service_secure_strdup (const gchar *str)
{
#ifdef HAVE_GNOME
	return gnome_keyring_memory_strdup (str);
#else
	return g_strdup (str);
#endif
}
