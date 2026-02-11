gst_mpdparser_get_lowest_representation (GList * Representations)
{
  GList *list = NULL;
  GstRepresentationNode *rep = NULL;
  GstRepresentationNode *lowest = NULL;

  if (Representations == NULL)
    return NULL;

  for (list = g_list_first (Representations); list; list = g_list_next (list)) {
    rep = (GstRepresentationNode *) list->data;
    if (rep && (!lowest || rep->bandwidth < lowest->bandwidth)) {
      lowest = rep;
    }
  }

  return lowest;
}
