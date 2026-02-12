static pj_status_t decode_msgint_attr(pj_pool_t *pool,
				      const pj_uint8_t *buf,
				      const pj_stun_msg_hdr *msghdr,
				      void **p_attr)
{
    pj_stun_msgint_attr *attr;

    PJ_UNUSED_ARG(msghdr);


    attr = PJ_POOL_ZALLOC_T(pool, pj_stun_msgint_attr);
    GETATTRHDR(buf, &attr->hdr);


    if (attr->hdr.length != 20)
	return PJNATH_ESTUNINATTRLEN;


    pj_memcpy(attr->hmac, buf+4, 20);


    *p_attr = attr;
    return PJ_SUCCESS;
}
