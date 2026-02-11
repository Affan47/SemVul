create_dirpath(char *dest, int len, const char *context, const char *ext, const char *folder)
{
	mode_t	mode = VOICEMAIL_DIR_MODE;
	int res;

	make_dir(dest, len, context, ext, folder);
	if ((res = ast_mkdir(dest, mode))) {
		ast_log(AST_LOG_WARNING, "ast_mkdir '%s' failed: %s\n", dest, strerror(res));
		return -1;
	}
	return 0;
}
