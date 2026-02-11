gdome_xmlNamedPreorderTraversal (xmlNode *root, xmlChar *tagURI, xmlChar *tagName, gulong *cur, gulong index) {
  xmlNode *iter, *ret = NULL;

  iter = root->children;

  if (*cur == index)
    return root;
  else if (iter == NULL)
    return NULL;

  while(iter != NULL && *cur<index) {
    if(iter->type == XML_ELEMENT_NODE &&
       (xmlStrEqual(gdome_xmlGetName(iter), tagName) ||
        xmlStrEqual(tagName, "*"))) {
      if(tagURI != NULL &&
         (xmlStrEqual(gdome_xmlGetNsURI(iter), tagURI) ||
          xmlStrEqual(tagURI, "*")))
        (*cur)++;
      else if(tagURI == NULL)
        (*cur)++;
    }
    ret = gdome_xmlNamedPreorderTraversal(iter, tagURI, tagName, cur, index);
    if(ret == NULL)
      iter = iter->next;
  }

  return ret;
}
