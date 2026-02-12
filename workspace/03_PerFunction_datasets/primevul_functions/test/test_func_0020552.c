static pj_status_t decode_empty_attr(pj_pool_t *pool,
				     const pj_uint8_t *buf,
				     const pj_stun_msg_hdr *msghdr,
				     void **p_attr)
{
    pj_stun_empty_attr *attr;

    PJ_UNUSED_ARG(msghdr);


    pj_assert(sizeof(pj_stun_empty_attr) == ATTR_HDR_LEN);


    attr = PJ_POOL_ZALLOC_T(pool, pj_stun_empty_attr);
    GETATTRHDR(buf, &attr->hdr);


    if (attr->hdr.length != 0)
	return PJNATH_ESTUNINATTRLEN;


    *p_attr = attr;

    return PJ_SUCCESS;
}
