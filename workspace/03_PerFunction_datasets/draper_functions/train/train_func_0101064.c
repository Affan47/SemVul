init_log_file(const char *log_file, int append)
{
	const char *open_mode = append ? "a" : "w";

	if (!(_log_file = fopen(log_file, open_mode))) {
		log_sys_error("fopen", log_file);
		return;
	}

	_log_to_file = 1;
}
