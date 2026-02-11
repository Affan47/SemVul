publish_value_background(dht_value_t *value,
	const lookup_rs_t *rs, const uint16 *status,
	publish_cb_t cb, void *arg)
{
	publish_t *pb;

	g_assert(size_is_positive(rs->path_len));
	lookup_result_check(rs);

	gnet_stats_inc_general(GNR_DHT_PUBLISHING_BG_ATTEMPTS);


	pb = publish_create(dht_value_key(value),
			PUBLISH_VALUE, publish_value_candidates(rs, status));

	pb->target.v.rs = lookup_result_refcnt_inc(rs);
	pb->target.v.value = value;
	pb->target.v.cb = cb;
	pb->target.v.arg = arg;
	pb->target.v.status = WCOPY_ARRAY(status, rs->path_len);
	pb->flags |= PB_F_BACKGROUND;
	pb->target.v.idx = publish_value_next_unstored(pb, 0);


	publish_async_iterate(pb);
	return pb;
}
