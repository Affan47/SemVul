host_create_from_chunk(int family, chunk_t address, u_int16_t port)
{
	private_host_t *this;

	switch (family)
	{
		case AF_INET:
			if (address.len < IPV4_LEN)
			{
				return NULL;
			}
			address.len = IPV4_LEN;
			break;
		case AF_INET6:
			if (address.len < IPV6_LEN)
			{
				return NULL;
			}
			address.len = IPV6_LEN;
			break;
		case AF_UNSPEC:
			switch (address.len)
			{
				case IPV4_LEN:
					family = AF_INET;
					break;
				case IPV6_LEN:
					family = AF_INET6;
					break;
				default:
					return NULL;
			}
			break;
		default:
			return NULL;
	}
	this = host_create_empty();
	this->address.sa_family = family;
	switch (family)
	{
		case AF_INET:
			memcpy(&this->address4.sin_addr.s_addr, address.ptr, address.len);
			this->address4.sin_port = htons(port);
			this->socklen = sizeof(struct sockaddr_in);
			break;
		case AF_INET6:
			memcpy(&this->address6.sin6_addr.s6_addr, address.ptr, address.len);
			this->address6.sin6_port = htons(port);
			this->socklen = sizeof(struct sockaddr_in6);
			break;
	}
	update_sa_len(this);
	return &this->public;
}
