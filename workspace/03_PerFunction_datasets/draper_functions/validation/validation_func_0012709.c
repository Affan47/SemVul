iprange_free(struct iprange_db **idb_ptr)
{
	struct iprange_db *idb;

	idb = *idb_ptr;
	if (idb) {
		iprange_db_check(idb);
		sorted_array_free(&idb->tab4);
		sorted_array_free(&idb->tab6);
		WFREE(idb);
		*idb_ptr = NULL;
	}
}
