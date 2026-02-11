active_packet(p, len)
    unsigned char *p;
    int len;
{
    int proto, i;
    struct protent *protp;

    if (len < PPP_HDRLEN)
	return 0;
    proto = PPP_PROTOCOL(p);
#ifdef PPP_FILTER
    if (active_filter.bf_len != 0
	&& bpf_filter(active_filter.bf_insns, frame, len, len) == 0)
	return 0;
#endif
    for (i = 0; (protp = protocols[i]) != NULL; ++i) {
	if (protp->protocol < 0xC000 && (protp->protocol & ~0x8000) == proto) {
	    if (!protp->enabled_flag)
		return 0;
	    if (protp->active_pkt == NULL)
		return 1;
	    return (*protp->active_pkt)(p, len);
	}
    }
    return 0;
}
