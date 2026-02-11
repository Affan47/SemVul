git_diff_blobs(
	git_blob *old_blob,
	git_blob *new_blob,
	git_diff_options *options,
	void *cb_data,
	git_diff_file_fn file_cb,
	git_diff_hunk_fn hunk_cb,
	git_diff_data_fn line_cb)
{
	diff_output_info info;
	git_diff_delta delta;
	mmfile_t old_data, new_data;
	git_map old_map, new_map;
	xpparam_t xdiff_params;
	xdemitconf_t xdiff_config;
	xdemitcb_t xdiff_callback;
	git_blob *new, *old;

	memset(&delta, 0, sizeof(delta));

	new = new_blob;
	old = old_blob;

	if (options && (options->flags & GIT_DIFF_REVERSE)) {
		git_blob *swap = old;
		old = new;
		new = swap;
	}

	if (old) {
		old_data.ptr  = (char *)git_blob_rawcontent(old);
		old_data.size = git_blob_rawsize(old);
		git_oid_cpy(&delta.old_file.oid, git_object_id((const git_object *)old));
	} else {
		old_data.ptr  = "";
		old_data.size = 0;
	}

	if (new) {
		new_data.ptr  = (char *)git_blob_rawcontent(new);
		new_data.size = git_blob_rawsize(new);
		git_oid_cpy(&delta.new_file.oid, git_object_id((const git_object *)new));
	} else {
		new_data.ptr  = "";
		new_data.size = 0;
	}


	delta.status = new ?
		(old ? GIT_DELTA_MODIFIED : GIT_DELTA_ADDED) :
		(old ? GIT_DELTA_DELETED : GIT_DELTA_UNTRACKED);

	if (git_oid_cmp(&delta.new_file.oid, &delta.old_file.oid) == 0)
		delta.status = GIT_DELTA_UNMODIFIED;

	delta.old_file.size = old_data.size;
	delta.new_file.size = new_data.size;

	fill_map_from_mmfile(&old_map, &old_data);
	fill_map_from_mmfile(&new_map, &new_data);

	if (file_is_binary_by_content(&delta, &old_map, &new_map) < 0)
		return -1;

	if (file_cb != NULL) {
		int error = file_cb(cb_data, &delta, 1);
		if (error < 0)
			return error;
	}


	if (delta.status == GIT_DELTA_UNMODIFIED)
		return 0;


	if (delta.binary == 1)
		return 0;

	info.diff    = NULL;
	info.delta   = &delta;
	info.cb_data = cb_data;
	info.hunk_cb = hunk_cb;
	info.line_cb = line_cb;

	setup_xdiff_options(options, &xdiff_config, &xdiff_params);
	memset(&xdiff_callback, 0, sizeof(xdiff_callback));
	xdiff_callback.outf = diff_output_cb;
	xdiff_callback.priv = &info;

	xdl_diff(&old_data, &new_data, &xdiff_params, &xdiff_config, &xdiff_callback);

	return 0;
}
