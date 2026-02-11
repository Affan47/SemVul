traverse_children (GNode    *node,
                   gpointer  data)
{
  TraverseClosure *closure = data;
  ClutterScoreEntry *entry = node->data;
  gboolean retval = FALSE;


  if (!entry)
    return TRUE;

  switch (closure->action)
    {
    case FIND_BY_TIMELINE:
      if (closure->d.timeline == entry->timeline)
        {
          closure->result = node;
          retval = TRUE;
        }
      break;

    case FIND_BY_ID:
      if (closure->d.id == entry->id)
        {
          closure->result = node;
          retval = TRUE;
        }
      break;

    case REMOVE_BY_ID:
      if (closure->d.id == entry->id)
        {

          g_node_traverse (node,
                           G_POST_ORDER,
                           G_TRAVERSE_ALL,
                           -1,
                           destroy_entry, NULL);


          closure->result = node;

          retval = TRUE;
        }
      break;

    case LIST_TIMELINES:
      closure->result = g_slist_prepend (closure->result, entry->timeline);
      retval = FALSE;
      break;
    }

  return retval;
}
