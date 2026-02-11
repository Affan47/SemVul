gimple_histogram_value (struct function *fun, gimple stmt)
{
  if (!VALUE_HISTOGRAMS (fun))
    return NULL;
  return (histogram_value) htab_find_with_hash (VALUE_HISTOGRAMS (fun), stmt,
						htab_hash_pointer (stmt));
}
