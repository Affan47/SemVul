lto_output_chain (struct output_block *ob, tree t, bool ref_p)
{
  int i, count;

  count = list_length (t);
  output_sleb128 (ob, count);
  for (i = 0; i < count; i++)
    {
      tree saved_chain;


      saved_chain = TREE_CHAIN (t);
      TREE_CHAIN (t) = NULL_TREE;

      lto_output_tree_or_ref (ob, t, ref_p);

      TREE_CHAIN (t) = saved_chain;
      t = TREE_CHAIN (t);
    }
}
