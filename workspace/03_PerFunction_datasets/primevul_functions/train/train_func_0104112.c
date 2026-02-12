soa_find_minttl(struct rr_parse* rr)
{
	uint16_t rlen = sldns_read_uint16(rr->ttl_data+4);
	if(rlen < 20)
		return 0;


	return (time_t)sldns_read_uint32(rr->ttl_data+6+rlen-4);
}
