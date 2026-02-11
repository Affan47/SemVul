io_finddescriptor(d)
	int d;
{
	int i;

	for (i = 0; i < ioc; ++i)
		if (iov[i].allocated) {
			if (d == iov[i].src.s ||	 d == iov[i].dst.s)
				return &iov[i];

			switch (iov[i].state.command) {
				case SOCKS_BIND:
				case SOCKS_BINDREPLY:
					if (!iov[i].state.extension.bind)
						break;


				case SOCKS_UDPASSOCIATE:
					if (d == iov[i].control.s)
						return &iov[i];
					break;

				default:
					break;
			}
		}

	return NULL;
}
