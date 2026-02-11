routerlist_free_all(void)
{
  routerlist_free(routerlist);
  routerlist = NULL;
  if (warned_nicknames) {
    SMARTLIST_FOREACH(warned_nicknames, char *, cp, tor_free(cp));
    smartlist_free(warned_nicknames);
    warned_nicknames = NULL;
  }
  if (trusted_dir_servers) {
    SMARTLIST_FOREACH(trusted_dir_servers, trusted_dir_server_t *, ds,
                      trusted_dir_server_free(ds));
    smartlist_free(trusted_dir_servers);
    trusted_dir_servers = NULL;
  }
  if (trusted_dir_certs) {
    DIGESTMAP_FOREACH(trusted_dir_certs, key, cert_list_t *, cl) {
      SMARTLIST_FOREACH(cl->certs, authority_cert_t *, cert,
                        authority_cert_free(cert));
      smartlist_free(cl->certs);
      tor_free(cl);
    } DIGESTMAP_FOREACH_END;
    digestmap_free(trusted_dir_certs, NULL);
    trusted_dir_certs = NULL;
  }
}
