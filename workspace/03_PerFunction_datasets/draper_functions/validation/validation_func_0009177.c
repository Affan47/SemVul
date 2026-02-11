nspace_get_by_prefix(flickrdf_nspace* list, const char *prefix)
{
  flickrdf_nspace* ns;
  size_t prefix_len = strlen(prefix);

  for(ns = list; ns; ns = ns->next) {
    if(ns->prefix_len == prefix_len && !strcmp(ns->prefix, prefix))
      break;
  }
  return ns;
}
