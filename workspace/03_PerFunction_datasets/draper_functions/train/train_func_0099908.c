add_roster(cnr room, jid userid)
{
  xmlnode store;
  xmlnode node;
  xmlnode old;
  char ujid[2048];

  if(room == NULL || userid == NULL)
  {
    log_warn(NAME, "[%s] ERR: Missing variable", FZONE);
    return -1;
  }

  snprintf(ujid, sizeof(ujid), "%s@%s", userid->user, userid->server);
  old = g_hash_table_lookup(room->roster, ujid);


  if(old == NULL)
  {
    store = xmlnode_new_tag("users");
  }
  else
  {
    store = xmlnode_dup(old);
    node = xmlnode_get_tag(store, spools(xmlnode_pool(store), "item?jid=", jid_full(userid), xmlnode_pool(store)));


    if(node != NULL)
    {
      log_debug(NAME, "[%s] DBG: Already in node, ignoring\n", FZONE);
      xmlnode_free(store);
      return 0;
    }
  }

  if(userid->resource != NULL)
  {
    log_debug(NAME, "[%s] adding entry (%s) for jid (%s)", FZONE, jid_full(userid), ujid);
    node = xmlnode_insert_tag(store, "item");
    xmlnode_put_attrib(node, "jid", jid_full(userid));
  }

  g_hash_table_insert(room->roster, g_strdup(ujid), store);

  return 1;
}
