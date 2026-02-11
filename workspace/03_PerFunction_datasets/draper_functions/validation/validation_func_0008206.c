ipa_init (void)
{
  static bool init_p = false;

  if (init_p)
    return;

  init_p = true;

  if (dump_file)
    reference_vars_to_consider = splay_tree_new (splay_tree_compare_ints, 0, 0);

  bitmap_obstack_initialize (&local_info_obstack);
  bitmap_obstack_initialize (&optimization_summary_obstack);
  all_module_statics = BITMAP_ALLOC (&optimization_summary_obstack);

  node_removal_hook_holder =
      cgraph_add_node_removal_hook (&remove_node_data, NULL);
  node_duplication_hook_holder =
      cgraph_add_node_duplication_hook (&duplicate_node_data, NULL);
}
