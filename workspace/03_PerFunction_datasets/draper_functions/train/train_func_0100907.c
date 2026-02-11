ves_icall_System_Security_Cryptography_RNGCryptoServiceProvider_RngGetBytes (gpointer handle, MonoArray *arry)
{
	gint file = GPOINTER_TO_INT (handle);
	guint32 len = mono_array_length (arry);
	guchar *buf = mono_array_addr (arry, guchar, 0);

	if (egd) {
		const char *socket_path = g_getenv ("MONO_EGD_SOCKET");

		if (socket_path == NULL)
			return NULL;
		get_entropy_from_server (socket_path, mono_array_addr (arry, guchar, 0), mono_array_length (arry));
		return (gpointer) -1;
	} else {

		gint count = 0;
		gint err;

		do {
			err = read (file, buf + count, len - count);
			if (err < 0) {
				if (errno == EINTR)
					continue;
				break;
			}
			count += err;
		} while (count < len);

		if (err < 0) {
			g_warning("Entropy error! Error in read (%s).", strerror (errno));

			return NULL;
		}
	}


	return handle;
}
