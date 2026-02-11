vacuum_index(VacPageList vacpagelist, Relation indrel,
			 double num_tuples, int keep_tuples)
{
	IndexBulkDeleteResult *stats;
	IndexVacuumInfo ivinfo;
	PGRUsage	ru0;

	pg_rusage_init(&ru0);

	ivinfo.index = indrel;
	ivinfo.vacuum_full = true;
	ivinfo.message_level = elevel;
	ivinfo.num_heap_tuples = num_tuples + keep_tuples;
	ivinfo.strategy = vac_strategy;


	stats = index_bulk_delete(&ivinfo, NULL, tid_reaped, (void *) vacpagelist);


	stats = index_vacuum_cleanup(&ivinfo, stats);

	if (!stats)
		return;


	vac_update_relstats(RelationGetRelid(indrel),
						stats->num_pages, stats->num_index_tuples,
						false, InvalidTransactionId);

	ereport(elevel,
			(errmsg("index \"%s\" now contains %.0f row versions in %u pages",
					RelationGetRelationName(indrel),
					stats->num_index_tuples,
					stats->num_pages),
			 errdetail("%.0f index row versions were removed.\n"
			 "%u index pages have been deleted, %u are currently reusable.\n"
					   "%s.",
					   stats->tuples_removed,
					   stats->pages_deleted, stats->pages_free,
					   pg_rusage_show(&ru0))));


	if (stats->num_index_tuples != num_tuples + keep_tuples)
	{
		if (stats->num_index_tuples > num_tuples + keep_tuples ||
			!vac_is_partial_index(indrel))
			ereport(WARNING,
					(errmsg("index \"%s\" contains %.0f row versions, but table contains %.0f row versions",
							RelationGetRelationName(indrel),
						  stats->num_index_tuples, num_tuples + keep_tuples),
					 errhint("Rebuild the index with REINDEX.")));
	}

	pfree(stats);
}
