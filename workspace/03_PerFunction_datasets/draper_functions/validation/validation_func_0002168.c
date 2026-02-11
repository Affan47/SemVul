wccpLowestIP(void)
{
    int loop;
    int found = 0;


    for (loop = 0; loop < ntohl(wccp_i_see_you.number); loop++) {
	assert(loop < WCCP_ACTIVE_CACHES);
	if (wccp_i_see_you.wccp_cache_entry[loop].ip_addr.s_addr < local_ip.s_addr)
	    return 0;
	if (wccp_i_see_you.wccp_cache_entry[loop].ip_addr.s_addr == local_ip.s_addr)
	    found = 1;
    }
    return found;
}
