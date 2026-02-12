static pj_status_t decode_string_attr(pj_pool_t *pool,
				      const pj_uint8_t *buf,
				      const pj_stun_msg_hdr *msghdr,
				      void **p_attr)
{
    pj_stun_string_attr *attr;
    pj_str_t value;

    PJ_UNUSED_ARG(msghdr);


    attr = PJ_POOL_ZALLOC_T(pool, pj_stun_string_attr);
    GETATTRHDR(buf, &attr->hdr);


    value.ptr = ((char*)buf + ATTR_HDR_LEN);
    value.slen = attr->hdr.length;


    pj_strdup(pool, &attr->value, &value);


    *p_attr = attr;

    return PJ_SUCCESS;

}
