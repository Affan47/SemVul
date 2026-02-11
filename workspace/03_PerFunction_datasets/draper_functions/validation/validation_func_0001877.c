dump_gimple_omp_atomic_store (pretty_printer *buffer, gimple gs, int spc,
                             int flags)
{
  if (flags & TDF_RAW)
    {
      dump_gimple_fmt (buffer, spc, flags, "%G <%T>", gs,
                       gimple_omp_atomic_store_val (gs));
    }
  else
    {
      pp_string (buffer, "#pragma omp atomic_store (");
      dump_generic_node (buffer, gimple_omp_atomic_store_val (gs),
	  		 spc, flags, false);
      pp_character (buffer, ')');
    }
}
