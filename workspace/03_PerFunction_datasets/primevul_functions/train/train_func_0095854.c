static void set_cookie(const struct mg_connection *conn,
                       char *user, char *referer) {
  char key[256], session_id[64], random[64];

  if(!strcmp(mg_get_request_info((struct mg_connection*)conn)->uri, "/metrics")
     || !strncmp(mg_get_request_info((struct mg_connection*)conn)->uri, GRAFANA_URL, strlen(GRAFANA_URL))
     || !strncmp(mg_get_request_info((struct mg_connection*)conn)->uri, POOL_MEMBERS_ASSOC_URL, strlen(POOL_MEMBERS_ASSOC_URL)))
    return;

  if(authorized_localhost_users_login_disabled(conn))
    return;


  snprintf(random, sizeof(random), "%d", rand());

  generate_session_id(session_id, random, user);


  mg_printf((struct mg_connection *)conn, "HTTP/1.1 302 Found\r\n"
	    "Set-Cookie: session=%s; path=/; max-age=%u;%s\r\n"
	    "Set-Cookie: user=%s; path=/; max-age=%u;%s\r\n"
	    "Location: %s%s\r\n\r\n",
	    session_id, HTTP_SESSION_DURATION, get_secure_cookie_attributes(mg_get_request_info((struct mg_connection*)conn)),
	    user, HTTP_SESSION_DURATION, get_secure_cookie_attributes(mg_get_request_info((struct mg_connection*)conn)),
	    ntop->getPrefs()->get_http_prefix(), referer ? referer : "/");


  snprintf(key, sizeof(key), "sessions.%s", session_id);
  ntop->getRedis()->set(key, user, HTTP_SESSION_DURATION);
  ntop->getTrace()->traceEvent(TRACE_INFO, "[HTTP] Set session sessions.%s", session_id);
}
