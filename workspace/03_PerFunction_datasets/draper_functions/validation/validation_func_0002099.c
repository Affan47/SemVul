expand_filepath_ex(const char *filepath, char *real_path, const char *relative_to, size_t relative_to_len TSRMLS_DC)
{
	cwd_state new_state;
	char cwd[MAXPATHLEN];
	int copy_len;

	if (!filepath[0]) {
		return NULL;
	} else if (IS_ABSOLUTE_PATH(filepath, strlen(filepath))) {
		cwd[0] = '\0';
	} else {
		const char *iam = SG(request_info).path_translated;
		const char *result;
		if (relative_to) {
			if (relative_to_len > MAXPATHLEN-1U) {
				return NULL;
			}
			result = relative_to;
			memcpy(cwd, relative_to, relative_to_len+1U);
		} else {
			result = VCWD_GETCWD(cwd, MAXPATHLEN);
		}

		if (!result && (iam != filepath)) {
			int fdtest = -1;

			fdtest = VCWD_OPEN(filepath, O_RDONLY);
			if (fdtest != -1) {


				copy_len = strlen(filepath) > MAXPATHLEN - 1 ? MAXPATHLEN - 1 : strlen(filepath);
				real_path = estrndup(filepath, copy_len);
				close(fdtest);
				return real_path;
			} else {
				cwd[0] = '\0';
			}
		} else if (!result) {
			cwd[0] = '\0';
		}
	}

	new_state.cwd = strdup(cwd);
	new_state.cwd_length = strlen(cwd);

	if (virtual_file_ex(&new_state, filepath, NULL, CWD_FILEPATH)) {
		free(new_state.cwd);
		return NULL;
	}

	if (real_path) {
		copy_len = new_state.cwd_length > MAXPATHLEN - 1 ? MAXPATHLEN - 1 : new_state.cwd_length;
		memcpy(real_path, new_state.cwd, copy_len);
		real_path[copy_len] = '\0';
	} else {
		real_path = estrndup(new_state.cwd, new_state.cwd_length);
	}
	free(new_state.cwd);

	return real_path;
}
