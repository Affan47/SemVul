_wapi_FD_CLR(guint32 fd, fd_set *set)
{
	gpointer handle = GUINT_TO_POINTER (fd);

	if (fd >= FD_SETSIZE) {
		WSASetLastError (WSAEINVAL);
		return;
	}

	if (_wapi_handle_type (handle) != WAPI_HANDLE_SOCKET) {
		WSASetLastError (WSAENOTSOCK);
		return;
	}

	FD_CLR (fd, set);
}
