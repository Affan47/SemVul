jcr_cdata(void *m, const char *cdata, int len) {
  if (jcr->current != NULL)
    xmlnode_insert_cdata(jcr->current, cdata, len);
}
