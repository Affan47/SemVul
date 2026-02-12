innodb_remove(

	ENGINE_HANDLE*		handle,
	const void*		cookie,
	const void*		key,
	const size_t		nkey,
	uint64_t		cas __attribute__((unused)),

	uint16_t		vbucket __attribute__((unused)))


{
	struct innodb_engine*	innodb_eng = innodb_handle(handle);
	struct default_engine*	def_eng = default_handle(innodb_eng);
	ENGINE_ERROR_CODE	err_ret = ENGINE_SUCCESS;
	innodb_conn_data_t*	conn_data;
	meta_cfg_info_t*	meta_info = innodb_eng->meta_info;
	ENGINE_ERROR_CODE	cacher_err = ENGINE_KEY_ENOENT;

	if (meta_info->del_option == META_CACHE_OPT_DISABLE) {
		return(ENGINE_SUCCESS);
	}

	if (meta_info->del_option == META_CACHE_OPT_DEFAULT
	    || meta_info->del_option == META_CACHE_OPT_MIX) {
		hash_item*	item = item_get(def_eng, key, nkey);

		if (item != NULL) {
			item_unlink(def_eng, item);
			item_release(def_eng, item);
			cacher_err = ENGINE_SUCCESS;
		}

		if (meta_info->del_option == META_CACHE_OPT_DEFAULT) {
			return(cacher_err);
		}
	}

	conn_data = innodb_conn_init(innodb_eng, cookie,
				     CONN_MODE_WRITE, IB_LOCK_X, false,
				     NULL);

	if (!conn_data) {
		return(ENGINE_TMPFAIL);
	}


	err_ret = innodb_api_delete(innodb_eng, conn_data, key, nkey);

	innodb_api_cursor_reset(innodb_eng, conn_data, CONN_OP_DELETE,
				err_ret == ENGINE_SUCCESS);

	return((cacher_err == ENGINE_SUCCESS) ? ENGINE_SUCCESS : err_ret);
}
