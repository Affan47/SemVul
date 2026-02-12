static void download_one_url(const char *url)
{
	bool use_proxy;
	int redir_limit;
	len_and_sockaddr *lsa;
	FILE *sfp;
	FILE *dfp;
	char *fname_out_alloc;
	char *redirected_path = NULL;
	struct host_info server;
	struct host_info target;

	server.allocated = NULL;
	target.allocated = NULL;
	server.user = NULL;
	target.user = NULL;

	parse_url(url, &target);


	use_proxy = (strcmp(G.proxy_flag, "off") != 0);
	if (use_proxy) {
		char *proxy = getenv(target.protocol[0] == 'f' ? "ftp_proxy" : "http_proxy");

		use_proxy = (proxy && proxy[0]);
		if (use_proxy)
			parse_url(proxy, &server);
	}
	if (!use_proxy) {
		server.protocol = target.protocol;
		server.port = target.port;
		if (ENABLE_FEATURE_IPV6) {

			server.host = server.allocated = xstrdup(target.host);
		} else {
			server.host = target.host;
		}
	}

	if (ENABLE_FEATURE_IPV6)
		strip_ipv6_scope_id(target.host);


	fname_out_alloc = NULL;
	if (!(option_mask32 & WGET_OPT_OUTNAME)) {
		G.fname_out = bb_get_last_path_component_nostrip(target.path);

		if (G.fname_out[0] == '/' || !G.fname_out[0])
			G.fname_out = (char*)"index.html";

		if (G.dir_prefix)
			G.fname_out = fname_out_alloc = concat_path_file(G.dir_prefix, G.fname_out);
		else {

			G.fname_out = fname_out_alloc = xstrdup(G.fname_out);
		}
	}
#if ENABLE_FEATURE_WGET_STATUSBAR
	G.curfile = bb_get_last_path_component_nostrip(G.fname_out);
#endif


	G.beg_range = 0;
	if (option_mask32 & WGET_OPT_CONTINUE) {
		G.output_fd = open(G.fname_out, O_WRONLY);
		if (G.output_fd >= 0) {
			G.beg_range = xlseek(G.output_fd, 0, SEEK_END);
		}


	}

	redir_limit = 16;
 resolve_lsa:
	lsa = xhost2sockaddr(server.host, server.port);
	if (!(option_mask32 & WGET_OPT_QUIET)) {
		char *s = xmalloc_sockaddr2dotted(&lsa->u.sa);
		fprintf(stderr, "Connecting to %s (%s)\n", server.host, s);
		free(s);
	}
 establish_session:

	G.got_clen = 0;
	G.chunked = 0;
	if (use_proxy || target.protocol[0] != 'f' ) {


		char *str;
		int status;


#if ENABLE_FEATURE_WGET_OPENSSL

		if (server.protocol == P_HTTPS) {


			int fd = spawn_https_helper_openssl(server.host, server.port);
# if ENABLE_FEATURE_WGET_HTTPS
			if (fd < 0) {
				sfp = open_socket(lsa);
				spawn_ssl_client(server.host, fileno(sfp),  0);
				goto socket_opened;
			}
# else

# endif
			sfp = fdopen(fd, "r+");
			if (!sfp)
				bb_die_memory_exhausted();
			goto socket_opened;
		}
		sfp = open_socket(lsa);
 socket_opened:
#elif ENABLE_FEATURE_WGET_HTTPS

		sfp = open_socket(lsa);
		if (server.protocol == P_HTTPS)
			spawn_ssl_client(server.host, fileno(sfp),  0);
#else

		sfp = open_socket(lsa);
#endif

		if (use_proxy) {
			SENDFMT(sfp, "GET %s://%s/%s HTTP/1.1\r\n",
				target.protocol, target.host,
				target.path);
		} else {
			SENDFMT(sfp, "%s /%s HTTP/1.1\r\n",
				(option_mask32 & WGET_OPT_POST_DATA) ? "POST" : "GET",
				target.path);
		}
		if (!USR_HEADER_HOST)
			SENDFMT(sfp, "Host: %s\r\n", target.host);
		if (!USR_HEADER_USER_AGENT)
			SENDFMT(sfp, "User-Agent: %s\r\n", G.user_agent);


		SENDFMT(sfp, "Connection: close\r\n");

#if ENABLE_FEATURE_WGET_AUTHENTICATION
		if (target.user && !USR_HEADER_AUTH) {
			SENDFMT(sfp, "Proxy-Authorization: Basic %s\r\n"+6,
				base64enc(target.user));
		}
		if (use_proxy && server.user && !USR_HEADER_PROXY_AUTH) {
			SENDFMT(sfp, "Proxy-Authorization: Basic %s\r\n",
				base64enc(server.user));
		}
#endif

		if (G.beg_range != 0 && !USR_HEADER_RANGE)
			SENDFMT(sfp, "Range: bytes=%"OFF_FMT"u-\r\n", G.beg_range);

#if ENABLE_FEATURE_WGET_LONG_OPTIONS
		if (G.extra_headers) {
			log_io(G.extra_headers);
			fputs(G.extra_headers, sfp);
		}

		if (option_mask32 & WGET_OPT_POST_DATA) {
			SENDFMT(sfp,
				"Content-Type: application/x-www-form-urlencoded\r\n"
				"Content-Length: %u\r\n"
				"\r\n"
				"%s",
				(int) strlen(G.post_data), G.post_data
			);
		} else
#endif
		{
			SENDFMT(sfp, "\r\n");
		}

		fflush(sfp);


#if SSL_SUPPORTED
		if (target.protocol == P_HTTPS) {


			shutdown(fileno(sfp), SHUT_WR);
		}
#endif


 read_response:
		fgets_trim_sanitize(sfp, "  %s\n");

		str = G.wget_buf;
		str = skip_non_whitespace(str);
		str = skip_whitespace(str);


		status = atoi(str);
		switch (status) {
		case 0:
		case 100:
			while (get_sanitized_hdr(sfp) != NULL)
				;
			goto read_response;


		case 200:

		case 201:


		case 202:


		case 203:


		case 204:


			if (G.beg_range != 0) {


				reset_beg_range_to_zero();
			}
			break;


		case 300:
		case 301:
		case 302:
		case 303:
			break;

		case 206:
			if (G.beg_range != 0)

				break;


		default:
			bb_error_msg_and_die("server returned error: %s", G.wget_buf);
		}


		while ((str = get_sanitized_hdr(sfp)) != NULL) {
			static const char keywords[] ALIGN1 =
				"content-length\0""transfer-encoding\0""location\0";
			enum {
				KEY_content_length = 1, KEY_transfer_encoding, KEY_location
			};
			smalluint key;


			char *s = strchrnul(str, '\0') - 1;
			while (s >= str && (*s == ' ' || *s == '\t')) {
				*s = '\0';
				s--;
			}
			key = index_in_strings(keywords, G.wget_buf) + 1;
			if (key == KEY_content_length) {
				G.content_len = BB_STRTOOFF(str, NULL, 10);
				if (G.content_len < 0 || errno) {
					bb_error_msg_and_die("content-length %s is garbage", str);
				}
				G.got_clen = 1;
				continue;
			}
			if (key == KEY_transfer_encoding) {
				if (strcmp(str_tolower(str), "chunked") != 0)
					bb_error_msg_and_die("transfer encoding '%s' is not supported", str);
				G.chunked = 1;
			}
			if (key == KEY_location && status >= 300) {
				if (--redir_limit == 0)
					bb_simple_error_msg_and_die("too many redirections");
				fclose(sfp);
				if (str[0] == '/') {
					free(redirected_path);
					target.path = redirected_path = xstrdup(str + 1);

				} else {
					parse_url(str, &target);
					if (!use_proxy) {

						free(server.allocated);
						server.allocated = NULL;
						server.protocol = target.protocol;
						server.host = target.host;


						server.port = target.port;
						free(lsa);
						goto resolve_lsa;
					}
				}
				goto establish_session;
			}
		}


		dfp = sfp;
	} else {


		sfp = prepare_ftp_session(&dfp, &target, lsa);
	}

	free(lsa);

	if (!(option_mask32 & WGET_OPT_SPIDER)) {
		if (G.output_fd < 0)
			G.output_fd = xopen(G.fname_out, G.o_flags);
		retrieve_file_data(dfp);
		if (!(option_mask32 & WGET_OPT_OUTNAME)) {
			xclose(G.output_fd);
			G.output_fd = -1;
		}
	} else {
		if (!(option_mask32 & WGET_OPT_QUIET))
			fprintf(stderr, "remote file exists\n");
	}

	if (dfp != sfp) {

		fclose(dfp);
		if (ftpcmd(NULL, NULL, sfp) != 226)
			bb_error_msg_and_die("ftp error: %s", G.wget_buf);

	}
	fclose(sfp);

	free(server.allocated);
	free(target.allocated);
	free(server.user);
	free(target.user);
	free(fname_out_alloc);
	free(redirected_path);
}
