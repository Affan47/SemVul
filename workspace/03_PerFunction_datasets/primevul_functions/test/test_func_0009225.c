static struct dst_entry *xfrm_dst_check(struct dst_entry *dst, u32 cookie)
{


	if (dst->obsolete < 0 && !stale_bundle(dst))
		return dst;

	return NULL;
}
