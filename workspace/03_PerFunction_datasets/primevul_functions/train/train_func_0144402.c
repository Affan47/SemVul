static char *detect_proxy(struct connectdata *conn)
{
  char *proxy = NULL;


  char proxy_env[128];
  const char *protop = conn->handler->scheme;
  char *envp = proxy_env;
  char *prox;


  while(*protop)
    *envp++ = (char)tolower((int)*protop++);


  strcpy(envp, "_proxy");


  prox = curl_getenv(proxy_env);


  if(!prox && !strcasecompare("http_proxy", proxy_env)) {

    Curl_strntoupper(proxy_env, proxy_env, sizeof(proxy_env));
    prox = curl_getenv(proxy_env);
  }

  if(prox)
    proxy = prox;
  else {
    proxy = curl_getenv("all_proxy");
    if(!proxy)
      proxy = curl_getenv("ALL_PROXY");
  }

  return proxy;
}
