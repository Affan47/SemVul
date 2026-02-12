R_API void r_bin_file_free(void  *_bf) {
	if (!_bf) {
		return;
	}
	RBinFile *bf = _bf;
	RBinPlugin *plugin = r_bin_file_cur_plugin (bf);


	if (plugin && plugin->destroy) {
		plugin->destroy (bf);
	}
	r_buf_free (bf->buf);
	if (bf->curxtr && bf->curxtr->destroy && bf->xtr_obj) {
		bf->curxtr->free_xtr ((void *)(bf->xtr_obj));
	}

	if (bf->sdb_addrinfo) {
		sdb_free (bf->sdb_addrinfo);
		bf->sdb_addrinfo = NULL;
	}
	free (bf->file);
	r_bin_object_free (bf->o);
	r_list_free (bf->xtr_data);
	if (bf->id != -1) {

		r_id_pool_kick_id (bf->rbin->ids->pool, bf->id);
	}
	(void) r_bin_object_delete (bf->rbin, bf->id);
	free (bf);
}
