thunar_transfer_node_free (ThunarTransferNode *node)
{
  ThunarTransferNode *next;


  while (node != NULL)
    {

      thunar_transfer_node_free (node->children);


      next = node->next;


      g_object_unref (node->source_file);


      g_slice_free (ThunarTransferNode, node);


      node = next;
    }
}
