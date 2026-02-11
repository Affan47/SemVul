sdbout_init (const char *input_file_name ATTRIBUTE_UNUSED)
{
  tree t;

  vec_alloc (deferred_global_decls, 12);


  sdbout_initialized = true;

  for (t = nreverse (preinit_symbols); t; t = TREE_CHAIN (t))
    sdbout_symbol (TREE_VALUE (t), 0);
  preinit_symbols = 0;
}
