static uint32_t *rpc_add_credentials(uint32_t *p)
{


	*p++ = htonl(1);
	*p++ = htonl(20);
	*p++ = 0;
	*p++ = 0;
	*p++ = 0;
	*p++ = 0;
	*p++ = 0;


	*p++ = 0;
	*p++ = 0;

	return p;
}
