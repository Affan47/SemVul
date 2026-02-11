edit_file(const struct passwd *pas, const char *file)
{
	const char *ptr;
	int pid = xvfork();

	if (pid) {
		wait4pid(pid);
		return;
	}


	change_identity(pas);
	setup_environment(DEFAULT_SHELL,
			SETUP_ENV_CHANGEENV | SETUP_ENV_TO_TMP,
			pas);
	ptr = getenv("VISUAL");
	if (!ptr) {
		ptr = getenv("EDITOR");
		if (!ptr)
			ptr = "vi";
	}

	BB_EXECLP(ptr, ptr, file, NULL);
	bb_perror_msg_and_die("exec %s", ptr);
}
