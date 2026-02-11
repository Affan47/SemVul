WSAStartup(guint32 requested, WapiWSAData *data)
{
	if (data == NULL) {
		return(WSAEFAULT);
	}


	if (requested < MAKEWORD(2,0)) {
		return(WSAVERNOTSUPPORTED);
	}

	startup_count++;


	data->wHighVersion = MAKEWORD(2,2);

	data->wVersion = requested < data->wHighVersion? requested:
		data->wHighVersion;

	DEBUG ("%s: high version 0x%x", __func__, data->wHighVersion);

	strncpy (data->szDescription, "WAPI", WSADESCRIPTION_LEN);
	strncpy (data->szSystemStatus, "groovy", WSASYS_STATUS_LEN);

	return(0);
}
