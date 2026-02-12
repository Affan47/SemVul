static char *detect_proxy(struct connectdata *conn)
{
  char *proxy = NULL;

#ifndef CURL_DISABLE_HTTP


  char *no_proxy=NULL;
  char proxy_env[128];

  no_proxy=curl_getenv("no_proxy");
  if(!no_proxy)
    no_proxy=curl_getenv("NO_PROXY");

  if(!check_noproxy(conn->host.name, no_proxy)) {

    const char *protop = conn->handler->scheme;
    char *envp = proxy_env;
    char *prox;


    while(*protop)
      *envp++ = (char)tolower((int)*protop++);


    strcpy(envp, "_proxy");


    prox=curl_getenv(proxy_env);


    if(!prox && !Curl_raw_equal("http_proxy", proxy_env)) {

      Curl_strntoupper(proxy_env, proxy_env, sizeof(proxy_env));
      prox=curl_getenv(proxy_env);
    }

    if(prox)
      proxy = prox;
    else {
      proxy = curl_getenv("all_proxy");
      if(!proxy)
        proxy=curl_getenv("ALL_PROXY");
    }
  }

  free(no_proxy);

#else

  (void)conn;
#endif

  return proxy;
}
