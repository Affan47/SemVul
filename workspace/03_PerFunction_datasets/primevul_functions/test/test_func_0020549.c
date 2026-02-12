static pj_status_t encode_string_attr(const void *a, pj_uint8_t *buf,
				      unsigned len,
				      const pj_stun_msg_hdr *msghdr,
				      unsigned *printed)
{
    const pj_stun_string_attr *ca =
	(const pj_stun_string_attr*)a;

    PJ_CHECK_STACK();

    PJ_UNUSED_ARG(msghdr);


    *printed = ((unsigned)ca->value.slen + ATTR_HDR_LEN + 3) & (~3);
    if (len < *printed) {
	*printed = 0;
	return PJ_ETOOSMALL;
    }

    PUTVAL16H(buf, 0, ca->hdr.type);


    if (msghdr->magic != PJ_STUN_MAGIC ||
	ca->hdr.type == PJ_STUN_ATTR_SOFTWARE)
    {


	PUTVAL16H(buf, 2, (pj_uint16_t)((ca->value.slen + 3) & (~3)));
    } else {

	PUTVAL16H(buf, 2, (pj_uint16_t)ca->value.slen);
    }


    pj_memcpy(buf+ATTR_HDR_LEN, ca->value.ptr, ca->value.slen);


    if (ca->value.slen & 0x03) {
	pj_uint8_t pad[3];
	pj_memset(pad, padding_char, sizeof(pad));
	pj_memcpy(buf+ATTR_HDR_LEN+ca->value.slen, pad,
		  4-(ca->value.slen & 0x03));
    }


    return PJ_SUCCESS;
}
