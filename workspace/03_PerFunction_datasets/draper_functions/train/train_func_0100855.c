update_branch(unsigned int idx, str** uri, str** dst_uri, str** path,
		qvalue_t* q, unsigned int* flags, struct socket_info** force_socket)
{
	if (dset_state==0 || idx>=nr_branches)
		return -1;


	if (uri) {

		if (*uri==NULL || (*uri)->len>MAX_URI_SIZE-1) {
			LM_ERR("empty or too long uri\n");
			return -1;
		}
		memcpy(branches[idx].uri, (*uri)->s, (*uri)->len);
		branches[idx].uri[(*uri)->len] = 0;
		branches[idx].len = (*uri)->len;
	}


	if (dst_uri) {
		if (*dst_uri && (*dst_uri)->len && (*dst_uri)->s) {
			if ((*dst_uri)->len > MAX_URI_SIZE - 1) {
				LM_ERR("too long dst_uri: %.*s\n",
					(*dst_uri)->len, (*dst_uri)->s);
				return -1;
			}
			memcpy(branches[idx].dst_uri, (*dst_uri)->s, (*dst_uri)->len);
			branches[idx].dst_uri[(*dst_uri)->len] = 0;
			branches[idx].dst_uri_len = (*dst_uri)->len;
		} else {
			branches[idx].dst_uri[0] = '\0';
			branches[idx].dst_uri_len = 0;
		}
	}


	if (path) {
		if (*path && (*path)->len && (*path)->s) {
			if ((*path)->len > MAX_PATH_SIZE - 1) {
				LM_ERR("too long path: %.*s\n", (*path)->len, (*path)->s);
				return -1;
			}
			memcpy(branches[idx].path, (*path)->s, (*path)->len);
			branches[idx].path[(*path)->len] = 0;
			branches[idx].path_len = (*path)->len;
		} else {
			branches[idx].path[0] = '\0';
			branches[idx].path_len = 0;
		}
	}


	if (q)
		branches[idx].q = *q;


	if (flags)
		branches[idx].flags = *flags;


	if (force_socket)
		branches[idx].force_send_socket = *force_socket;

	return 0;
}
