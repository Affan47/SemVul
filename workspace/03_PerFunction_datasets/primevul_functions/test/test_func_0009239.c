static struct flow_cache_object *xfrm_bundle_flo_get(struct flow_cache_object *flo)
{
	struct xfrm_dst *xdst = container_of(flo, struct xfrm_dst, flo);
	struct dst_entry *dst = &xdst->u.dst;

	if (xdst->route == NULL) {


		if (xdst->num_xfrms > 0)
			return NULL;
	} else if (dst->flags & DST_XFRM_QUEUE) {
		return NULL;
	} else {

		if (stale_bundle(dst))
			return NULL;
	}

	dst_hold(dst);
	return flo;
}
