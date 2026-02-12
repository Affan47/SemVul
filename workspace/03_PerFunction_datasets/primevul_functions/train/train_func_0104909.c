static int ldb_kv_index_dn_and(struct ldb_module *module,
			       struct ldb_kv_private *ldb_kv,
			       const struct ldb_parse_tree *tree,
			       struct dn_list *list)
{
	struct ldb_context *ldb;
	unsigned int i;
	bool found;

	ldb = ldb_module_get_ctx(module);

	list->dn = NULL;
	list->count = 0;


	for (i=0; i<tree->u.list.num_elements; i++) {
		const struct ldb_parse_tree *subtree = tree->u.list.elements[i];
		int ret;

		if (subtree->operation != LDB_OP_EQUALITY ||
		    !ldb_kv_index_unique(
			ldb, ldb_kv, subtree->u.equality.attr)) {
			continue;
		}

		ret = ldb_kv_index_dn(module, ldb_kv, subtree, list);
		if (ret == LDB_ERR_NO_SUCH_OBJECT) {

			return LDB_ERR_NO_SUCH_OBJECT;
		}
		if (ret == LDB_SUCCESS) {


			return LDB_SUCCESS;
		}
	}


	found = false;

	for (i=0; i<tree->u.list.num_elements; i++) {
		const struct ldb_parse_tree *subtree = tree->u.list.elements[i];
		struct dn_list *list2;
		int ret;

		list2 = talloc_zero(list, struct dn_list);
		if (list2 == NULL) {
			return ldb_module_oom(module);
		}

		ret = ldb_kv_index_dn(module, ldb_kv, subtree, list2);

		if (ret == LDB_ERR_NO_SUCH_OBJECT) {

			list->dn = NULL;
			list->count = 0;
			talloc_free(list2);
			return LDB_ERR_NO_SUCH_OBJECT;
		}

		if (ret != LDB_SUCCESS) {

			talloc_free(list2);
			continue;
		}

		if (!found) {
			talloc_reparent(list2, list, list->dn);
			list->dn = list2->dn;
			list->count = list2->count;
			found = true;
		} else if (!list_intersect(ldb, ldb_kv, list, list2)) {
			talloc_free(list2);
			return LDB_ERR_OPERATIONS_ERROR;
		}

		if (list->count == 0) {
			list->dn = NULL;
			return LDB_ERR_NO_SUCH_OBJECT;
		}

		if (list->count < 2) {

			return LDB_SUCCESS;
		}
	}

	if (!found) {

		return LDB_ERR_OPERATIONS_ERROR;
	}

	return LDB_SUCCESS;
}
