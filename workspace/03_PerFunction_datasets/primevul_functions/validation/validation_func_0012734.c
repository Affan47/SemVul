struct child_process *git_connect(int fd[2], const char *url,
				  const char *prog, int flags)
{
	char *hostandport, *path;
	struct child_process *conn = &no_fork;
	enum protocol protocol;
	struct strbuf cmd = STRBUF_INIT;


	signal(SIGCHLD, SIG_DFL);

	protocol = parse_connect_url(url, &hostandport, &path);
	if ((flags & CONNECT_DIAG_URL) && (protocol != PROTO_SSH)) {
		printf("Diag: url=%s\n", url ? url : "NULL");
		printf("Diag: protocol=%s\n", prot_name(protocol));
		printf("Diag: hostandport=%s\n", hostandport ? hostandport : "NULL");
		printf("Diag: path=%s\n", path ? path : "NULL");
		conn = NULL;
	} else if (protocol == PROTO_GIT) {


		char *target_host = getenv("GIT_OVERRIDE_VIRTUAL_HOST");
		if (target_host)
			target_host = xstrdup(target_host);
		else
			target_host = xstrdup(hostandport);

		transport_check_allowed("git");


		if (git_use_proxy(hostandport))
			conn = git_proxy_connect(fd, hostandport);
		else
			git_tcp_connect(fd, hostandport, flags);


		packet_write_fmt(fd[1],
			     "%s %s%chost=%s%c",
			     prog, path, 0,
			     target_host, 0);
		free(target_host);
	} else {
		conn = xmalloc(sizeof(*conn));
		child_process_init(conn);

		if (looks_like_command_line_option(path))
			die("strange pathname '%s' blocked", path);

		strbuf_addstr(&cmd, prog);
		strbuf_addch(&cmd, ' ');
		sq_quote_buf(&cmd, path);


		conn->env = local_repo_env;
		conn->use_shell = 1;
		conn->in = conn->out = -1;
		if (protocol == PROTO_SSH) {
			const char *ssh;
			int needs_batch = 0;
			int port_option = 'p';
			char *ssh_host = hostandport;
			const char *port = NULL;
			transport_check_allowed("ssh");
			get_host_and_port(&ssh_host, &port);

			if (!port)
				port = get_port(ssh_host);

			if (flags & CONNECT_DIAG_URL) {
				printf("Diag: url=%s\n", url ? url : "NULL");
				printf("Diag: protocol=%s\n", prot_name(protocol));
				printf("Diag: userandhost=%s\n", ssh_host ? ssh_host : "NULL");
				printf("Diag: port=%s\n", port ? port : "NONE");
				printf("Diag: path=%s\n", path ? path : "NULL");

				free(hostandport);
				free(path);
				free(conn);
				return NULL;
			}

			if (looks_like_command_line_option(ssh_host))
				die("strange hostname '%s' blocked", ssh_host);

			ssh = get_ssh_command();
			if (ssh)
				handle_ssh_variant(ssh, 1, &port_option,
						   &needs_batch);
			else {


				conn->use_shell = 0;

				ssh = getenv("GIT_SSH");
				if (!ssh)
					ssh = "ssh";
				else
					handle_ssh_variant(ssh, 0,
							   &port_option,
							   &needs_batch);
			}

			argv_array_push(&conn->args, ssh);
			if (flags & CONNECT_IPV4)
				argv_array_push(&conn->args, "-4");
			else if (flags & CONNECT_IPV6)
				argv_array_push(&conn->args, "-6");
			if (needs_batch)
				argv_array_push(&conn->args, "-batch");
			if (port) {
				argv_array_pushf(&conn->args,
						 "-%c", port_option);
				argv_array_push(&conn->args, port);
			}
			argv_array_push(&conn->args, ssh_host);
		} else {
			transport_check_allowed("file");
		}
		argv_array_push(&conn->args, cmd.buf);

		if (start_command(conn))
			die("unable to fork");

		fd[0] = conn->out;
		fd[1] = conn->in;
		strbuf_release(&cmd);
	}
	free(hostandport);
	free(path);
	return conn;
}
