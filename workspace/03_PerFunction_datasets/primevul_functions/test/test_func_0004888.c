static void apply_name_table( unsigned *count,
			      pj_str_t nametable[],
		    	      const pj_str_t *src,
			      pj_pool_t *pool,
			      pj_str_t *dst)
{
    unsigned i;


    for (i=0; i<*count; ++i) {
	if (pj_stricmp(&nametable[i], src) == 0)
	    break;
    }


    if (i != *count) {
	dst->ptr = nametable[i].ptr;
	dst->slen = nametable[i].slen;
	return;
    }


    pj_strdup(pool, dst, src);

    if (*count < PJ_DNS_MAX_NAMES_IN_NAMETABLE) {
	nametable[*count].ptr = dst->ptr;
	nametable[*count].slen = dst->slen;

	++(*count);
    }
}
