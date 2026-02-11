getnodebyaddr_ether(const char *inaddr, int len, int family) {
	struct ether_addr ea = {.ether_addr_octet = {0xAA, 0x00, 0x04, 0x00}};
	int i;

	memcpy((void*)laddr, (void*)inaddr, 2);

	dp.n_addr     = (unsigned char *)&laddr;
	dp.n_length   = 2;
	dp.n_addrtype = AF_DECnet;

	memcpy((void*)&ea.ether_addr_octet[4], (void*)laddr, 2);

	if ( ether_ntohost(nodename, &ea) != 0 )
	    return NULL;

	for (i = 0; nodename[i] != 0; i++) {
	    if ( nodename[i] == '.' ) {
	        nodename[i] = 0;
	        break;
	    }
	}

	dp.n_name = nodename;
	return &dp;
}
