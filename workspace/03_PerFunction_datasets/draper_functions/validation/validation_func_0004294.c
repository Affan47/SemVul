rdatasetiter_destroy(dns_rdatasetiter_t **iteratorp) {
	rbtdb_rdatasetiter_t *rbtiterator;

	rbtiterator = (rbtdb_rdatasetiter_t *)(*iteratorp);

	if (rbtiterator->common.version != NULL)
		closeversion(rbtiterator->common.db,
			     &rbtiterator->common.version, ISC_FALSE);
	detachnode(rbtiterator->common.db, &rbtiterator->common.node);
	isc_mem_put(rbtiterator->common.db->mctx, rbtiterator,
		    sizeof(*rbtiterator));

	*iteratorp = NULL;
}
