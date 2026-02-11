rfc1035_aton_ipv4(const char *p, struct in_addr *in4)
{
int	dummy;
RFC1035_UINT32 n=doaton(p, &dummy);
union	{
	unsigned char addr[4];
	struct in_addr n;
	} u;

	u.addr[3]=n;
	u.addr[2]=n >> 8;
	u.addr[1]=n >> 16;
	u.addr[0]=n >> 24;

	if (dummy)	errno=EINVAL;
	*in4=u.n;
	return (dummy);
}
