save_torrent_to(const char* path, rhash_context* rctx)
{
	FILE* fd;
	struct rsh_stat_struct stat_buf;
	size_t text_len;
	char *str;


	text_len = rhash_transmit(RMSG_BT_GET_TEXT, rctx, RHASH_STR2UPTR(&str), 0);
	assert(text_len != RHASH_ERROR);

	if(rsh_stat(path, &stat_buf) >= 0) {

		char *bak_path = str_append(path, ".bak");
		unlink(bak_path);
		rename(path, bak_path);
		free(bak_path);
	}


	fd = rsh_fopen_bin(path, "wb");
	if(fd && text_len == fwrite(str, 1, text_len, fd) &&
		!ferror(fd) && !fflush(fd))
	{
		log_msg(_("%s saved\n"), path);
	} else {
		log_file_error(path);
	}
	if(fd) fclose(fd);
}
