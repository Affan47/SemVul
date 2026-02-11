get_bindaddr_for_server_proxy(const managed_proxy_t *mp)
{
  char *bindaddr_result = NULL;
  char *bindaddr_tmp = NULL;
  smartlist_t *string_tmp = smartlist_new();

  tor_assert(mp->is_server);

  SMARTLIST_FOREACH_BEGIN(mp->transports_to_launch, char *, t) {
    bindaddr_tmp = get_stored_bindaddr_for_server_transport(t);

    smartlist_add_asprintf(string_tmp, "%s-%s", t, bindaddr_tmp);

    tor_free(bindaddr_tmp);
  } SMARTLIST_FOREACH_END(t);

  bindaddr_result = smartlist_join_strings(string_tmp, ",", 0, NULL);

  SMARTLIST_FOREACH(string_tmp, char *, t, tor_free(t));
  smartlist_free(string_tmp);

  return bindaddr_result;
}
