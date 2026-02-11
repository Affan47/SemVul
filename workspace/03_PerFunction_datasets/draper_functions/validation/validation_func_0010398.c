gen_icache_h (lf *file,
	      insn_list *semantic,
	      function_entry * functions, int max_nr_words)
{
  int word_nr;
  for (word_nr = 0; word_nr <= max_nr_words; word_nr++)
    {
      lf_printf (file, "typedef ");
      print_icache_function_type (file);
      lf_printf (file, " %sidecode_icache_%d\n(",
		 options.module.global.prefix.l, word_nr);
      print_icache_function_formal (file, word_nr);
      lf_printf (file, ");\n");
      lf_printf (file, "\n");
    }
  if (options.gen.code == generate_calls && options.gen.icache)
    {
      function_entry_traverse (file, functions,
			       print_icache_internal_function_declaration,
			       NULL);
      while (semantic != NULL)
	{
	  print_icache_declaration (file,
				    semantic->insn,
				    semantic->expanded_bits,
				    semantic->opcodes,
				    semantic->nr_prefetched_words);
	  semantic = semantic->next;
	}
    }
  else
    {
      lf_print__this_file_is_empty (file, "generating jump engine");
    }
}
