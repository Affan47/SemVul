ssh_login(Sensitive *sensitive, const char *orighost,
    struct sockaddr *hostaddr, u_short port, struct passwd *pw, int timeout_ms)
{
	char *host;
	char *server_user, *local_user;

	local_user = xstrdup(pw->pw_name);
	server_user = options.user ? options.user : local_user;


	host = xstrdup(orighost);
	lowercase(host);


	ssh_exchange_identification(timeout_ms);


	packet_set_nonblocking();


	if (compat20) {
		ssh_kex2(host, hostaddr, port);
		ssh_userauth2(local_user, server_user, host, sensitive);
	} else {
		ssh_kex(host, hostaddr);
		ssh_userauth1(local_user, server_user, host, sensitive);
	}
	free(local_user);
}
