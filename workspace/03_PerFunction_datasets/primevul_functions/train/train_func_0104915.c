static int ldb_kv_index_dn_leaf(struct ldb_module *module,
				struct ldb_kv_private *ldb_kv,
				const struct ldb_parse_tree *tree,
				struct dn_list *list)
{
	if (ldb_kv->disallow_dn_filter &&
	    (ldb_attr_cmp(tree->u.equality.attr, "dn") == 0)) {

		list->dn = NULL;
		list->count = 0;
		return LDB_SUCCESS;
	}
	if (tree->u.equality.attr[0] == '@') {

		list->dn = NULL;
		list->count = 0;
		return LDB_SUCCESS;
	}
	if (ldb_attr_dn(tree->u.equality.attr) == 0) {
		enum key_truncation truncation = KEY_NOT_TRUNCATED;
		struct ldb_dn *dn
			= ldb_dn_from_ldb_val(list,
					      ldb_module_get_ctx(module),
					      &tree->u.equality.value);
		if (dn == NULL) {

			list->dn = NULL;
			list->count = 0;
			return LDB_SUCCESS;
		}


		return ldb_kv_index_dn_base_dn(
		    module, ldb_kv, dn, list, &truncation);


	} else if ((ldb_kv->cache->GUID_index_attribute != NULL) &&
		   (ldb_attr_cmp(tree->u.equality.attr,
				 ldb_kv->cache->GUID_index_attribute) == 0)) {
		int ret;
		struct ldb_context *ldb = ldb_module_get_ctx(module);
		list->dn = talloc_array(list, struct ldb_val, 1);
		if (list->dn == NULL) {
			ldb_module_oom(module);
			return LDB_ERR_OPERATIONS_ERROR;
		}


		ret = ldb_kv->GUID_index_syntax->canonicalise_fn(
		    ldb, list->dn, &tree->u.equality.value, &list->dn[0]);
		if (ret != LDB_SUCCESS) {
			return LDB_ERR_OPERATIONS_ERROR;
		}
		list->count = 1;
		return LDB_SUCCESS;
	}

	return ldb_kv_index_dn_simple(module, ldb_kv, tree, list);
}
