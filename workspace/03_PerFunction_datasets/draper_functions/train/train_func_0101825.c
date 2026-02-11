func_arp_packet(struct packet *p, void *arg)
{
	struct host_up_info *hui = (struct host_up_info *) arg;
	struct arpeth_hdr *arpethh;
	unsigned int ip;

	arpethh  = (struct arpeth_hdr *)(p->p_arph + 1);
	ip = *(unsigned int *) arpethh->ar_sip;

	if (p->p_arph->ar_op == htons(ARPOP_REPLY) &&
	    ntohl(ip) >= ntohl(hui->start_addr) &&
	    ntohl(ip) <= ntohl(hui->end_addr)) {
		packet_want(p);
		list_produce(&l_arp_packet, p);
	}
}
