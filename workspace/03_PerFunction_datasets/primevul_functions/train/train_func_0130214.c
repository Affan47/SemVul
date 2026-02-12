innodb_switch_mapping(

	ENGINE_HANDLE*		handle,
	const void*		cookie,
	const char*		name,


	size_t*			name_len,


	bool			has_prefix)

{
	struct innodb_engine*	innodb_eng = innodb_handle(handle);
	innodb_conn_data_t*	conn_data;
	char			new_name[KEY_MAX_LENGTH];
	meta_cfg_info_t*	meta_info = innodb_eng->meta_info;
	char*			new_map_name;
	unsigned int		new_map_name_len = 0;
	char*			last;
	meta_cfg_info_t*	new_meta_info;
	int			sep_len = 0;

	if (has_prefix) {
		char*		sep = NULL;

		assert(*name_len > 2 && name[0] == '@' && name[1] == '@');
		assert(*name_len < KEY_MAX_LENGTH);

		memcpy(new_name, &name[2], (*name_len) - 2);

		new_name[*name_len - 2] = 0;

		GET_OPTION(meta_info, OPTION_ID_TBL_MAP_SEP, sep, sep_len);

		assert(sep_len > 0);

		new_map_name = strtok_r(new_name, sep, &last);

		if (new_map_name == NULL) {
			return(ENGINE_KEY_ENOENT);
		}

		new_map_name_len = strlen(new_map_name);
	} else {


		if (name == NULL) {
			return(ENGINE_KEY_ENOENT);
		}

		new_map_name = (char*) name;
		new_map_name_len = *name_len;
	}

	conn_data = innodb_eng->server.cookie->get_engine_specific(cookie);


	if (conn_data && conn_data->conn_meta
	    && (new_map_name_len
		== conn_data->conn_meta->col_info[CONTAINER_NAME].col_name_len)
	    && (strcmp(
		new_map_name,
		conn_data->conn_meta->col_info[CONTAINER_NAME].col_name) == 0)) {
		goto get_key_name;
	}

	new_meta_info = innodb_config(
		new_map_name, new_map_name_len, &innodb_eng->meta_hash);

	if (!new_meta_info) {
		return(ENGINE_KEY_ENOENT);
	}


	if (conn_data) {
		innodb_conn_clean_data(conn_data, false, false);


		conn_data->conn_meta = new_meta_info;
	}

	conn_data = innodb_conn_init(innodb_eng, cookie,
				     CONN_MODE_NONE, 0, false,
				     new_meta_info);

	assert(conn_data->conn_meta == new_meta_info);

get_key_name:


	if (has_prefix) {
		assert(*name_len >= strlen(new_map_name) + 2);

		if (*name_len >= strlen(new_map_name) + 2 + sep_len) {
			*name_len -= strlen(new_map_name) + 2 + sep_len;
		} else {


			*name_len  = 0;
		}
	}

	return(ENGINE_SUCCESS);
}
