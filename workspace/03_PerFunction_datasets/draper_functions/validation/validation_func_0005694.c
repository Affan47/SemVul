print_semantic_function_actual (lf *file, int nr_prefetched_words)
{
  int nr = 0;
  int word_nr;
  if (options.gen.icache || nr_prefetched_words < 0)
    {
      nr += lf_printf (file, "sd, cache_entry, cia");
    }
  else
    {
      if (options.gen.smp)
	nr += lf_printf (file, "cpu");
      else
	nr += lf_printf (file, "sd");
      for (word_nr = 0; word_nr < nr_prefetched_words; word_nr++)
	nr += lf_printf (file, ", instruction_%d", word_nr);
      nr += lf_printf (file, ", cia");
    }
  return nr;
}
