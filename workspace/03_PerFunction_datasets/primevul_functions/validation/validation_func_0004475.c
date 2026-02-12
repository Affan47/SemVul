static int tcp_connect(struct tunnel *tunnel)
{
	int ret, handle;
	struct sockaddr_in server;
	char *env_proxy;

	handle = socket(AF_INET, SOCK_STREAM, 0);
	if (handle == -1) {
		log_error("socket: %s\n", strerror(errno));
		goto err_socket;
	}
	env_proxy = getenv("https_proxy");
	if (env_proxy == NULL)
		env_proxy = getenv("HTTPS_PROXY");
	if (env_proxy == NULL)
		env_proxy = getenv("all_proxy");
	if (env_proxy == NULL)
		env_proxy = getenv("ALL_PROXY");
	if (env_proxy != NULL) {
		char *proxy_host, *proxy_port;

		env_proxy = strdup(env_proxy);
		if (env_proxy == NULL) {
			log_error("strdup: %s\n", strerror(errno));
			goto err_strdup;
		}

		if (*env_proxy && env_proxy[strlen(env_proxy) - 1] == '/')
			env_proxy[strlen(env_proxy) - 1] = '\0';

		proxy_host = strstr(env_proxy, "://");
		if (proxy_host == NULL)
			proxy_host = env_proxy;
		else
			proxy_host += 3;

		proxy_port = index(proxy_host, ':');
		if (proxy_port != NULL) {
			proxy_port[0] = '\0';
			proxy_port++;
			server.sin_port = htons(strtoul(proxy_port, NULL, 10));
		} else {
			server.sin_port = htons(tunnel->config->gateway_port);
		}

		if (*proxy_host && proxy_host[strlen(proxy_host) - 1] == '/')
			proxy_host[strlen(proxy_host) - 1] = '\0';
		log_debug("proxy_host: %s\n", proxy_host);
		log_debug("proxy_port: %s\n", proxy_port);
		server.sin_addr.s_addr = inet_addr(proxy_host);

		if (server.sin_addr.s_addr == INADDR_NONE) {
			const struct addrinfo hints = { .ai_family = AF_INET };
			struct addrinfo *result = NULL;

			ret = getaddrinfo(proxy_host, NULL, &hints, &result);
			if (ret) {
				if (ret == EAI_SYSTEM)
					log_error("getaddrinfo: %s\n", strerror(errno));
				else
					log_error("getaddrinfo: %s\n", gai_strerror(ret));
				goto err_connect;
			}

			server.sin_addr = ((struct sockaddr_in *)
			                   result->ai_addr)->sin_addr;
			freeaddrinfo(result);
		}
	} else {
		server.sin_port = htons(tunnel->config->gateway_port);
		server.sin_addr = tunnel->config->gateway_ip;
	}

	log_debug("server_addr: %s\n", inet_ntoa(server.sin_addr));
	log_debug("server_port: %u\n", ntohs(server.sin_port));
	server.sin_family = AF_INET;
	memset(&(server.sin_zero), '\0', 8);
	log_debug("gateway_addr: %s\n", inet_ntoa(tunnel->config->gateway_ip));
	log_debug("gateway_port: %u\n", tunnel->config->gateway_port);

	ret = connect(handle, (struct sockaddr *) &server, sizeof(server));
	if (ret) {
		log_error("connect: %s\n", strerror(errno));
		goto err_connect;
	}

	if (env_proxy != NULL) {
		char request[128];


		sprintf(request, "CONNECT %s:%u HTTP/1.1\r\nHost: %s:%u\r\n\r\n",
		        inet_ntoa(tunnel->config->gateway_ip),
		        tunnel->config->gateway_port,
		        inet_ntoa(tunnel->config->gateway_ip),
		        tunnel->config->gateway_port);
		ssize_t bytes_written = write(handle, request, strlen(request));
		if (bytes_written != strlen(request)) {
			log_error("write error while talking to proxy: %s\n",
			          strerror(errno));
			goto err_connect;
		}


		const char *response = NULL;

		memset(&(request), '\0', sizeof(request));
		for (int j = 0; response == NULL; j++) {


			ssize_t bytes_read = read(handle, &(request[j]), 1);
			if (bytes_read < 1) {
				log_error("Proxy response is unexpectedly large and cannot fit in the %lu-bytes buffer.\n",
				          ARRAY_SIZE(request));
				goto err_proxy_response;
			}


			static const char HTTP_STATUS_200[] = "200";
			response = strstr(request, HTTP_STATUS_200);


			if (response != NULL) {


				static const char *const HTTP_EOL[] = {
					"\r\n\r\n",
					"\n\n"
				};
				const char *eol = NULL;
				for (int i = 0; (i < ARRAY_SIZE(HTTP_EOL)) &&
				     (eol == NULL); i++)
					eol = strstr(response, HTTP_EOL[i]);
				response = eol;
			}

			if (j > ARRAY_SIZE(request) - 2) {
				log_error("Proxy response does not contain \"%s\" as expected.\n",
				          HTTP_STATUS_200);
				goto err_proxy_response;
			}
		}

		free(env_proxy);
	}

	return handle;

err_proxy_response:
err_connect:
	free(env_proxy);
err_strdup:
	close(handle);
err_socket:
	return -1;
}
