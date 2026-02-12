PJ_DEF(pj_status_t) pj_dns_make_query( void *packet,
				       unsigned *size,
				       pj_uint16_t id,
				       int qtype,
				       const pj_str_t *name)
{
    pj_uint8_t *p = (pj_uint8_t*)packet;
    const char *startlabel, *endlabel, *endname;
    pj_size_t d;


    PJ_ASSERT_RETURN(packet && size && qtype && name, PJ_EINVAL);


    d = sizeof(pj_dns_hdr) + name->slen + 4;


    PJ_ASSERT_RETURN(*size >= d, PJLIB_UTIL_EDNSQRYTOOSMALL);


    pj_assert(sizeof(pj_dns_hdr)==12);
    pj_bzero(p, sizeof(struct pj_dns_hdr));
    write16(p+0, id);
    write16(p+2, (pj_uint16_t)PJ_DNS_SET_RD(1));
    write16(p+4, (pj_uint16_t)1);


    p = ((pj_uint8_t*)packet)+sizeof(pj_dns_hdr);


    startlabel = endlabel = name->ptr;
    endname = name->ptr + name->slen;
    while (endlabel != endname) {
	while (endlabel != endname && *endlabel != '.')
	    ++endlabel;
	*p++ = (pj_uint8_t)(endlabel - startlabel);
	pj_memcpy(p, startlabel, endlabel-startlabel);
	p += (endlabel-startlabel);
	if (endlabel != endname && *endlabel == '.')
	    ++endlabel;
	startlabel = endlabel;
    }
    *p++ = '\0';


    write16(p, (pj_uint16_t)qtype);
    p += 2;


    write16(p, 1);
    p += 2;


    *size = (unsigned)(p - (pj_uint8_t*)packet);

    return 0;
}
