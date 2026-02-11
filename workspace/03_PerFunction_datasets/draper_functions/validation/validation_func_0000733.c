ipa_prop_write_jump_functions (cgraph_node_set set)
{
  struct cgraph_node *node;
  struct output_block *ob;
  unsigned int count = 0;
  cgraph_node_set_iterator csi;

  if (!ipa_node_params_vector)
    return;

  ob = create_output_block (LTO_section_jump_functions);
  ob->cgraph_node = NULL;
  for (csi = csi_start (set); !csi_end_p (csi); csi_next (&csi))
    {
      node = csi_node (csi);
      if (node->analyzed && IPA_NODE_REF (node) != NULL)
	count++;
    }

  lto_output_uleb128_stream (ob->main_stream, count);


  for (csi = csi_start (set); !csi_end_p (csi); csi_next (&csi))
    {
      node = csi_node (csi);
      if (node->analyzed && IPA_NODE_REF (node) != NULL)
        ipa_write_node_info (ob, node);
    }
  lto_output_1_stream (ob->main_stream, 0);
  produce_asm (ob, NULL);
  destroy_output_block (ob);
}
