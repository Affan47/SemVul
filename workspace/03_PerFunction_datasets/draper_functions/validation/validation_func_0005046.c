node_send_qrt(struct gnutella_node *n, struct routing_table *query_table)
{
	g_assert(GNET_PROPERTY(current_peermode) != NODE_P_NORMAL);
	g_assert(NODE_IS_ULTRA(n));
	g_assert(NODE_IS_CONNECTED(n));
	g_assert(query_table != NULL);
	g_assert(n->qrt_update == NULL);

	n->qrt_update = qrt_update_create(n, n->sent_query_table);
	if (n->sent_query_table) {
		qrt_unref(n->sent_query_table);
	}
	n->sent_query_table = qrt_ref(query_table);


	if (NODE_IS_CONNECTED(n)) {
		node_send_patch_step(n);
		node_fire_node_flags_changed(n);
	}
}
