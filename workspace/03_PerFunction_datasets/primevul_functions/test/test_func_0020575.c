PJ_DEF(pj_stun_attr_hdr*) pj_stun_attr_clone( pj_pool_t *pool,
					      const pj_stun_attr_hdr *attr)
{
    const struct attr_desc *adesc;


    adesc = find_attr_desc(attr->type);
    if (adesc) {
	return (pj_stun_attr_hdr*) (*adesc->clone_attr)(pool, attr);
    } else {

	const pj_stun_binary_attr *bin_attr = (const pj_stun_binary_attr*)
					       attr;
	PJ_ASSERT_RETURN(bin_attr->magic == PJ_STUN_MAGIC, NULL);
	if (bin_attr->magic == PJ_STUN_MAGIC) {
	    return (pj_stun_attr_hdr*) clone_binary_attr(pool, attr);
	} else {
	    return NULL;
	}
    }
}
