static void mstate(struct Curl_easy *data, CURLMstate state
#ifdef DEBUGBUILD
                   , int lineno
#endif
)
{
  CURLMstate oldstate = data->mstate;
  static const init_multistate_func finit[CURLM_STATE_LAST] = {
    NULL,
    NULL,
    Curl_init_CONNECT,

  };

#if defined(DEBUGBUILD) && defined(CURL_DISABLE_VERBOSE_STRINGS)
  (void) lineno;
#endif

  if(oldstate == state)

    return;

  data->mstate = state;

#if defined(DEBUGBUILD) && !defined(CURL_DISABLE_VERBOSE_STRINGS)
  if(data->mstate >= CURLM_STATE_CONNECT_PEND &&
     data->mstate < CURLM_STATE_COMPLETED) {
    long connection_id = -5000;

    if(data->easy_conn)
      connection_id = data->easy_conn->connection_id;

    infof(data,
          "STATE: %s => %s handle %p; line %d (connection #%ld)\n",
          statename[oldstate], statename[data->mstate],
          (void *)data, lineno, connection_id);
  }
#endif

  if(state == CURLM_STATE_COMPLETED)

    data->multi->num_alive--;


  if(finit[state])
    finit[state](data);
}
