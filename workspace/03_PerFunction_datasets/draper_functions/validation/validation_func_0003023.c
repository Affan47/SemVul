prefix_to_scan(struct prefix_entry *pref, struct scan_entry *scan){
	u_int16_t mask;
	u_int8_t words;
	unsigned int i;

	sanitize_ipv6_prefix(&(pref->ip6), pref->len);
	scan->start= pref->ip6;
	scan->cur= scan->start;

	words= pref->len/16;

	for(i=0; i< words; i++)
		(scan->end).s6_addr16[i]= (pref->ip6).s6_addr16[i];

	for(i= (words+1); i<8; i++){
		(scan->end).s6_addr16[i]= htons(0xffff);
	}

	mask=0xffff;

	for(i=0; i< (pref->len % 16); i++)
		mask= mask>>1;

	(scan->end).s6_addr16[words]= (scan->start).s6_addr16[words] | htons(mask);
}
