dns_cache_flushnode(dns_cache_t *cache, dns_name_t *name,
		    isc_boolean_t tree)
{
	isc_result_t result;
	dns_dbnode_t *node = NULL;
	dns_db_t *db = NULL;

	if (dns_name_equal(name, dns_rootname))
		return (dns_cache_flush(cache));

	LOCK(&cache->lock);
	if (cache->db != NULL)
		dns_db_attach(cache->db, &db);
	UNLOCK(&cache->lock);
	if (db == NULL)
		return (ISC_R_SUCCESS);

	if (tree) {
		result = cleartree(cache->db, name);
	} else {
		result = dns_db_findnode(cache->db, name, ISC_FALSE, &node);
		if (result == ISC_R_NOTFOUND) {
			result = ISC_R_SUCCESS;
			goto cleanup_db;
		}
		if (result != ISC_R_SUCCESS)
			goto cleanup_db;
		result = clearnode(cache->db, node);
		dns_db_detachnode(cache->db, &node);
	}

 cleanup_db:
	dns_db_detach(&db);
	return (result);
}
