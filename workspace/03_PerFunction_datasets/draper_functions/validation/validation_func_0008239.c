fc_ns_query_free ( struct refcnt *refcnt ) {
	struct fc_ns_query *query =
		container_of ( refcnt, struct fc_ns_query, refcnt );

	fc_peer_put ( query->peer );
	fc_port_put ( query->port );
	free ( query );
}
