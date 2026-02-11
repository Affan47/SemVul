nvpair_database_remove( struct nvpair_database *db, const char *key )
{
	const char *nkey = strdup(key);

	struct nvpair *nv = hash_table_remove(db->table,nkey);
	if(db->logdir && nv) {
		log_delete(db,nkey);
		log_flush(db);
	}
	return nv;
}
