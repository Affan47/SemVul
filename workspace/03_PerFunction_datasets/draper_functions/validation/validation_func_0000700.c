get_node_value (xmlNodePtr node, const gchar *node_id)
{
  gchar *value;
  xmlXPathContextPtr xpath_ctx;
  xmlXPathObjectPtr xpath_res;

  xpath_ctx = xmlXPathNewContext (node->doc);
  if (!xpath_ctx) {
    return NULL;
  }

  xpath_res = xmlXPathEvalExpression ((xmlChar *) node_id, xpath_ctx);
  if (!xpath_res) {
    xmlXPathFreeContext (xpath_ctx);
    return NULL;
  }

  if (xpath_res->nodesetval->nodeTab) {
    value =
      (gchar *) xmlNodeListGetString (node->doc,
                                      xpath_res->nodesetval->nodeTab[0]->xmlChildrenNode,
                                      1);
  } else {
    value = NULL;
  }

  xmlXPathFreeObject (xpath_res);
  xmlXPathFreeContext (xpath_ctx);

  return value;
}
