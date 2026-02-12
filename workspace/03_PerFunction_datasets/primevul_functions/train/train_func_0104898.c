static int ldb_kv_index_dn_one(struct ldb_module *module,
			       struct ldb_kv_private *ldb_kv,
			       struct ldb_dn *parent_dn,
			       struct dn_list *list,
			       enum key_truncation *truncation)
{

	list->strict = true;
	return ldb_kv_index_dn_attr(
	    module, ldb_kv, LDB_KV_IDXONE, parent_dn, list, truncation);
}
