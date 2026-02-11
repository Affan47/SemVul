HttpProxyOptions_free(HttpProxyOptions** hpo)
{
  assert(hpo != NULL);
  if (hpo == NULL) {
    return;
  }
  assert((*hpo) != NULL);
  if ((*hpo) == NULL) {
    return;
  }
  if ((*hpo)->proxyname) {
    free((*hpo)->proxyname);
    (*hpo)->proxyname = NULL;
  }
  if ((*hpo)->proxyport) {
    free((*hpo)->proxyport);
    (*hpo)->proxyport = NULL;
  }
  if ((*hpo)->proxyauth_cred) {
    free((*hpo)->proxyauth_cred);
    (*hpo)->proxyauth_cred = NULL;
  }
  free((*hpo));
  (*hpo) = NULL;
}
