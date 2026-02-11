cfg_cfgfile_get_next_opt(con)
	const CFG_CONTEXT con;
{
	char *buf;
	int ret_val;

	con->error_code = CFG_OK;


	if (con->fhandle == NULL) {
		con->fhandle = con->filename != NULL
			? fopen(con->filename, "r")
			: NULL;
		if (con->fhandle == NULL) {
			con->error_code = CFG_ERROR_FILE_NOT_FOUND;
			return con->error_code;
		}

		if (con->flags & CFG_FILE_LINE_POS_USAGE) {


			if (con->begin_pos < 0) {
				con->error_code = CFG_ERROR_SEEK_ERROR;
				return con->error_code;
			}

			if (con->begin_pos > 0) {
				con->cur_idx     = 0;
				con->cur_idx_tmp = 0;


				while (con->cur_idx_tmp < con->begin_pos) {
					switch (fgetc(con->fhandle)) {
						case EOF:
							con->error_code = CFG_ERROR_SEEK_ERROR;
							return con->error_code;
						case '\n':
							con->cur_idx_tmp++;
					}
				}
			}
		}
		else {
			if (
					fseek(con->fhandle, con->begin_pos, SEEK_SET) != 0) {
				con->error_code = CFG_ERROR_SEEK_ERROR;
				return con->error_code;
			}
		}
	}


	while (1) {

		if (con->flags & CFG_FILE_LINE_POS_USAGE) {
			con->cur_idx     += con->cur_idx_tmp;
			con->cur_idx_tmp  = 0;
		}


		con->error_code = get_multi_line(con, &buf);
		if (con->error_code != CFG_OK) {
			if (buf != NULL)
				free(buf);

			return con->error_code;
		}


		if (buf != NULL && con->prop[CFG_FILE_STOP_PREFIX] != NULL) {
			if (buf == PLATON_FUNC(strdyn_str2)(buf,
						con->prop[CFG_FILE_STOP_PREFIX], NULL)) {
				__cfg_free_currents(con);
				con->cur_opt    = buf;
				con->error_code = CFG_ERROR_STOP_STR;
				return con->error_code;
			}
		}


		if ((con->size >= 0 && cfg_get_cur_idx(con) >= con->begin_pos + con->size)
				|| feof(con->fhandle)) {
			if (buf != NULL)
				free(buf);

			return con->error_code;
		}

		__cfg_free_currents(con);

		if (__cfg_cfgfile_set_currents(con, buf) != CFG_OK) {
			con->error_code = CFG_ERROR_NOMEM;
			return con->error_code;
		}

		free(buf);

		con->error_code = __cfg_process_currents(con, &ret_val, NULL);
		if (con->error_code != CFG_OK)
			return con->error_code;

		if (ret_val > 0)
			return ret_val;
	}

	return con->error_code;
}
