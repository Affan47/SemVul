yenta_sock_init(struct pcmcia_socket *sock)
{
	struct yenta_socket *socket = container_of(sock, struct yenta_socket, socket);

	exca_writeb(socket, I365_GBLCTL, 0x00);
	exca_writeb(socket, I365_GENCTL, 0x00);


	yenta_interrogate(socket);

	yenta_clear_maps(socket);

	if (socket->type && socket->type->sock_init)
		socket->type->sock_init(socket);


	cb_writel(socket, CB_SOCKET_MASK, CB_CDMASK);

	return 0;
}
