rhash_torrent_add_file(torrent_ctx *ctx, const char* path, uint64_t filesize)
{
	size_t len = strlen(path);
	file_n_size_info* info = (file_n_size_info*)rsh_malloc(sizeof(uint64_t) + len + 1);
	info->size = filesize;
	memcpy(info->path, path, len + 1);
	rsh_vector_add_ptr(&ctx->files, info);


	if(ctx->blocks_hashes.size == 0 && ctx->index == 0) {

		ctx->piece_length = rhash_torrent_default_piece_length(filesize);
	}
}
