discard_stream(int s, servtab_t *sep UNUSED_PARAM)
{
#if BB_MMU
	while (safe_read(s, line, LINE_SIZE) > 0)
		continue;
#else


	xmove_fd(s, STDIN_FILENO);

	close(STDOUT_FILENO);
	xopen(bb_dev_null, O_WRONLY);

	xdup2(STDOUT_FILENO, STDERR_FILENO);
	BB_EXECVP("cat", (char**)cat_args);

#endif
}
