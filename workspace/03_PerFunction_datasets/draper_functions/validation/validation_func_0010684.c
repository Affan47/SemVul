gnac_profiles_xml_engine_get_list_values(XMLDoc      *doc,
                                         const gchar *expr)
{
  xmlXPathObjectPtr  xpath_obj = gnac_profiles_xml_engine_evaluate_query(
      expr, doc->xpath_context);
  if (!xpath_obj) return NULL;

  xmlNodeSetPtr nodes = xpath_obj->nodesetval;
  if (xmlXPathNodeSetIsEmpty(nodes)) {
    xmlXPathFreeObject(xpath_obj);
    return NULL;
  }

  gint i;
  GList *list = NULL;

  for (i = 0; i < nodes->nodeNr; i++) {
    xmlNode *current_node = nodes->nodeTab[i];

    if (!gnac_profiles_xml_engine_is_i18n_node(current_node)) {
      Value *val = g_malloc(sizeof(Value));
      val->name = gettext(
          (gchar *) xmlNodeGetContent(current_node->children));
      val->value =
          (gchar *) xmlNodeGetContent(current_node->properties->children);
      list = g_list_prepend(list, val);
    }
  }

  xmlXPathFreeObject(xpath_obj);

  return g_list_reverse(list);
}
