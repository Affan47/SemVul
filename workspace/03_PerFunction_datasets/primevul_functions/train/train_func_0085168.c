socket_flush_if_writable(void)
{
	int			res;


	if (PqSendPointer == PqSendStart)
		return 0;


	if (PqCommBusy)
		return 0;


	socket_set_nonblocking(true);

	PqCommBusy = true;
	res = internal_flush();
	PqCommBusy = false;
	return res;
}
