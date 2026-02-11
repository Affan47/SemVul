git_odb_backend_pack(git_odb_backend **backend_out, const char *objects_dir)
{
	struct pack_backend *backend = NULL;
	git_buf path = GIT_BUF_INIT;

	backend = git__calloc(1, sizeof(struct pack_backend));
	GITERR_CHECK_ALLOC(backend);

	if (git_vector_init(&backend->packs, 8, packfile_sort__cb) < 0 ||
		git_buf_joinpath(&path, objects_dir, "pack") < 0)
	{
		git__free(backend);
		return -1;
	}

	if (git_path_isdir(git_buf_cstr(&path)) == true) {
		backend->pack_folder = git_buf_detach(&path);
	}

	backend->parent.read = &pack_backend__read;
	backend->parent.read_prefix = &pack_backend__read_prefix;
	backend->parent.read_header = NULL;
	backend->parent.exists = &pack_backend__exists;
	backend->parent.foreach = &pack_backend__foreach;
	backend->parent.writepack = &pack_backend__writepack;
	backend->parent.free = &pack_backend__free;

	*backend_out = (git_odb_backend *)backend;

	git_buf_free(&path);

	return 0;
}
