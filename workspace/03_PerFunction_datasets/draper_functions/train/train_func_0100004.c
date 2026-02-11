ib_sa_path_rec_callback(struct ib_sa_query *sa_query,
				    int status,
				    struct ib_sa_mad *mad)
{
	struct ib_sa_path_query *query =
		container_of(sa_query, struct ib_sa_path_query, sa_query);

	if (mad) {
		struct ib_sa_path_rec rec;

		ib_unpack(path_rec_table, ARRAY_SIZE(path_rec_table),
			  mad->data, &rec);
		rec.net = NULL;
		rec.ifindex = 0;
		memset(rec.dmac, 0, ETH_ALEN);
		query->callback(status, &rec, query->context);
	} else
		query->callback(status, NULL, query->context);
}
