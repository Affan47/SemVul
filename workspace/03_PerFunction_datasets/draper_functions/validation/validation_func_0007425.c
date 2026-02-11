gegl_node_get_pad_proxy (GeglNode    *graph,
                         const gchar *name,
                         gboolean     is_graph_input)
{
  GeglNode *node = graph;
  GeglPad  *pad;

  pad = gegl_node_get_pad (node, name);
  if (!pad)
    {
      GeglNode *nop      = NULL;
      GeglPad  *nop_pad  = NULL;
      gchar    *nop_name = NULL;

      nop_name = g_strconcat ("proxynop-", name, NULL);
      nop      = g_object_new (GEGL_TYPE_NODE, "operation", "gegl:nop", "name", nop_name, NULL);
      nop_pad  = gegl_node_get_pad (nop, is_graph_input ? "input" : "output");
      g_free (nop_name);

      gegl_node_add_child (graph, nop);
      g_object_unref (nop);


      {
        GeglPad *new_pad = g_object_new (GEGL_TYPE_PAD, NULL);
        gegl_pad_set_param_spec (new_pad, nop_pad->param_spec);
        gegl_pad_set_node (new_pad, nop);
        gegl_pad_set_name (new_pad, name);
        gegl_node_add_pad (node, new_pad);
      }

      g_object_set_data (G_OBJECT (nop), "graph", graph);

      if (!is_graph_input)
        {
          g_signal_connect (G_OBJECT (nop), "invalidated",
                            G_CALLBACK (graph_source_invalidated), graph);
        }
      return nop;
    }
  return gegl_pad_get_node (pad);
}
