int ldb_kv_search_indexed(struct ldb_kv_context *ac, uint32_t *match_count)
{
	struct ldb_context *ldb = ldb_module_get_ctx(ac->module);
	struct ldb_kv_private *ldb_kv = talloc_get_type(
	    ldb_module_get_private(ac->module), struct ldb_kv_private);
	struct dn_list *dn_list;
	int ret;
	enum ldb_scope index_scope;
	enum key_truncation scope_one_truncation = KEY_NOT_TRUNCATED;


	if (!ldb_kv->cache->attribute_indexes &&
	    !ldb_kv->cache->one_level_indexes && ac->scope != LDB_SCOPE_BASE) {

		return LDB_ERR_OPERATIONS_ERROR;
	}

	dn_list = talloc_zero(ac, struct dn_list);
	if (dn_list == NULL) {
		return ldb_module_oom(ac->module);
	}


	if (ac->scope == LDB_SCOPE_ONELEVEL &&
	    !ldb_kv->cache->one_level_indexes) {
		index_scope = LDB_SCOPE_SUBTREE;
	} else {
		index_scope = ac->scope;
	}

	switch (index_scope) {
	case LDB_SCOPE_BASE:


		return ldb_operr(ldb);

	case LDB_SCOPE_ONELEVEL:


		ret = ldb_kv_index_dn_one(ac->module,
					  ldb_kv,
					  ac->base,
					  dn_list,
					  &scope_one_truncation);
		if (ret != LDB_SUCCESS) {
			talloc_free(dn_list);
			return ret;
		}


		if (ldb_kv->cache->GUID_index_attribute != NULL) {
			struct dn_list *idx_one_tree_list
				= talloc_zero(ac, struct dn_list);
			if (idx_one_tree_list == NULL) {
				return ldb_module_oom(ac->module);
			}

			if (!ldb_kv->cache->attribute_indexes) {
				talloc_free(idx_one_tree_list);
				talloc_free(dn_list);
				return LDB_ERR_OPERATIONS_ERROR;
			}


			ret = ldb_kv_index_dn(
			    ac->module, ldb_kv, ac->tree, idx_one_tree_list);
			if (ret == LDB_SUCCESS) {
				if (!list_intersect(ldb,
						    ldb_kv,
						    dn_list,
						    idx_one_tree_list)) {
					talloc_free(idx_one_tree_list);
					talloc_free(dn_list);
					return LDB_ERR_OPERATIONS_ERROR;
				}
			}
		}
		break;

	case LDB_SCOPE_SUBTREE:
	case LDB_SCOPE_DEFAULT:
		if (!ldb_kv->cache->attribute_indexes) {
			talloc_free(dn_list);
			return LDB_ERR_OPERATIONS_ERROR;
		}


		ret = ldb_kv_index_dn(ac->module, ldb_kv, ac->tree, dn_list);
		if (ret != LDB_SUCCESS) {
			talloc_free(dn_list);
			return ret;
		}
		break;
	}


	ret = ldb_kv_index_filter(
	    ldb_kv, dn_list, ac, match_count, scope_one_truncation);
	talloc_free(dn_list);
	return ret;
}
