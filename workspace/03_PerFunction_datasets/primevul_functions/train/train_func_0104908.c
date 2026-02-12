int ldb_kv_reindex(struct ldb_module *module)
{
	struct ldb_kv_private *ldb_kv = talloc_get_type(
	    ldb_module_get_private(module), struct ldb_kv_private);
	int ret;
	struct ldb_kv_reindex_context ctx;


	if (ldb_kv->read_only) {
		return LDB_ERR_UNWILLING_TO_PERFORM;
	}

	if (ldb_kv_cache_reload(module) != 0) {
		return LDB_ERR_OPERATIONS_ERROR;
	}


	ldb_kv_index_transaction_cancel(module);

	ret = ldb_kv_index_transaction_start(module);
	if (ret != LDB_SUCCESS) {
		return ret;
	}


	ret = ldb_kv->kv_ops->iterate(ldb_kv, delete_index, module);
	if (ret < 0) {
		struct ldb_context *ldb = ldb_module_get_ctx(module);
		ldb_asprintf_errstring(ldb, "index deletion traverse failed: %s",
				       ldb_errstring(ldb));
		return LDB_ERR_OPERATIONS_ERROR;
	}

	ctx.module = module;
	ctx.error = 0;
	ctx.count = 0;

	ret = ldb_kv->kv_ops->iterate(ldb_kv, re_key, &ctx);
	if (ret < 0) {
		struct ldb_context *ldb = ldb_module_get_ctx(module);
		ldb_asprintf_errstring(ldb, "key correction traverse failed: %s",
				       ldb_errstring(ldb));
		return LDB_ERR_OPERATIONS_ERROR;
	}

	if (ctx.error != LDB_SUCCESS) {
		struct ldb_context *ldb = ldb_module_get_ctx(module);
		ldb_asprintf_errstring(ldb, "reindexing failed: %s", ldb_errstring(ldb));
		return ctx.error;
	}

	ctx.error = 0;
	ctx.count = 0;


	ret = ldb_kv->kv_ops->iterate(ldb_kv, re_index, &ctx);
	if (ret < 0) {
		struct ldb_context *ldb = ldb_module_get_ctx(module);
		ldb_asprintf_errstring(ldb, "reindexing traverse failed: %s",
				       ldb_errstring(ldb));
		return LDB_ERR_OPERATIONS_ERROR;
	}

	if (ctx.error != LDB_SUCCESS) {
		struct ldb_context *ldb = ldb_module_get_ctx(module);
		ldb_asprintf_errstring(ldb, "reindexing failed: %s", ldb_errstring(ldb));
		return ctx.error;
	}

	if (ctx.count > 10000) {
		ldb_debug(ldb_module_get_ctx(module),
			  LDB_DEBUG_WARNING,
			  "Reindexing: re_index successful on %s, "
			  "final index write-out will be in transaction commit",
			  ldb_kv->kv_ops->name(ldb_kv));
	}
	return LDB_SUCCESS;
}
