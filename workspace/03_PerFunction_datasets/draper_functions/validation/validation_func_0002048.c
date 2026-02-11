flickcurl_build_tag_namespace(flickcurl* fc, xmlXPathContextPtr xpathCtx,
                              const xmlChar* root_xpathExpr)
{
  flickcurl_tag_namespace** tag_namespaces;
  flickcurl_tag_namespace* result = NULL;

  tag_namespaces = flickcurl_build_tag_namespaces(fc, xpathCtx, root_xpathExpr,
                                                  NULL);
  if(tag_namespaces) {
    int i;

    result = tag_namespaces[0];

    for(i = 1; tag_namespaces[i]; i++)
      flickcurl_free_tag_namespace(tag_namespaces[i]);
    free(tag_namespaces);
  }

  return result;
}
