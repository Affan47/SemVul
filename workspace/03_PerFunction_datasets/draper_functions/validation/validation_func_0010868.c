inaddrcmp(struct sockaddr_in *sin1, struct sockaddr_in *sin2)
{
	return (sin1->sin_addr.s_addr != sin2->sin_addr.s_addr) || (sin1->sin_port != sin2->sin_port);
}
