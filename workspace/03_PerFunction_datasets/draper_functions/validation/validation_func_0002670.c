onBoxUnitChanged(VisuBox *box, gfloat fact, gpointer user_data)
{
  VisuData *data = VISU_DATA(user_data);
  VisuNodeArrayIter iter;

  DBG_fprintf(stderr, "Visu Data: caught 'UnitChanged' signal with factor %g.\n", fact);


  data->priv->translation[0] *= fact;
  data->priv->translation[1] *= fact;
  data->priv->translation[2] *= fact;
  visu_node_array_iterNew(VISU_NODE_ARRAY(data), &iter);
  for( visu_node_array_iterStart(VISU_NODE_ARRAY(data), &iter); iter.node;
       visu_node_array_iterNext(VISU_NODE_ARRAY(data), &iter))
    {
      iter.node->xyz[0] *= fact;
      iter.node->xyz[1] *= fact;
      iter.node->xyz[2] *= fact;
      iter.node->translation[0] *= fact;
      iter.node->translation[1] *= fact;
      iter.node->translation[2] *= fact;
    }

  g_signal_emit_by_name(G_OBJECT(data), "PositionChanged", (VisuElement*)0, NULL);


  visu_box_setMargin(box, visu_node_array_getMaxElementSize(VISU_NODE_ARRAY(data)) +
                     visu_data_getAllNodeExtens(data, (VisuBox*)0), FALSE);
  DBG_fprintf(stderr, "Visu Data: done 'UnitChanged'.\n");
}
