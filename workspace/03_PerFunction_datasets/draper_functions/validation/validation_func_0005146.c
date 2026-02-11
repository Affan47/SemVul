get_vendor(struct ether_addr *mac){
	int hash;
	struct macname *base;
	struct macname *next;

	hash = MACNAME_HASH(mac->ETHER_ADDR_OCTET[0],
	                    mac->ETHER_ADDR_OCTET[1],
	                    mac->ETHER_ADDR_OCTET[2]);
	base = &macname_base[hash];
	next = base->next;
	while(next != base){
		if(next->octet[0] == mac->ETHER_ADDR_OCTET[0] &&
		   next->octet[1] == mac->ETHER_ADDR_OCTET[1] &&
		   next->octet[2] == mac->ETHER_ADDR_OCTET[2]){
			return next->name;
		}
		next = next->next;
	}

	return NULL;
}
