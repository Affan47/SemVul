visu_data_node_newWithCallbacks(const gchar *name,
                                         VisuDataNodeFromStringFunc setAsString,
                                         VisuDataNodeToStringFunc getAsString)
{
  VisuDataNode *data;

  g_return_val_if_fail(name, (GObject*)0);
  g_return_val_if_fail(setAsString && getAsString, (GObject*)0);


  data = VISU_DATA_NODE(g_object_new(VISU_DATA_NODE_TYPE, NULL));
  g_return_val_if_fail(data, (GObject*)0);


  data->id   = g_strdup(name);
  data->type = (GType)0;
  data->setAsString = setAsString;
  data->getAsString = getAsString;

  return G_OBJECT(data);
}
