udp_serv_open(SHORT portnum)
{
	int	result;
	struct	sockaddr_in	sin;
	sin.sin_family = AF_INET;
	sin.sin_port = portnum;
	BLOCK_ZERO(sin.sin_zero, sizeof(sin.sin_zero));
	sin.sin_addr.s_addr = INADDR_ANY;


	if  ((result = socket(PF_INET, SOCK_DGRAM, udpproto)) < 0)
		return  -1;

	if  (bind(result, (struct sockaddr *) &sin, sizeof(sin)) < 0)  {
		close(result);
		return  -1;
	}
	return  result;
}
