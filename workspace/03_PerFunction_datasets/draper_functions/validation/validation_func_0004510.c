lookup_address_in_function_table (struct comp_unit *unit,
				  bfd_vma addr,
				  struct funcinfo **function_ptr,
				  const char **functionname_ptr)
{
  struct funcinfo* each_func;
  struct funcinfo* best_fit = NULL;
  struct arange *arange;

  for (each_func = unit->function_table;
       each_func;
       each_func = each_func->prev_func)
    {
      for (arange = &each_func->arange;
	   arange;
	   arange = arange->next)
	{
	  if (addr >= arange->low && addr < arange->high)
	    {
	      if (!best_fit
		  || (arange->high - arange->low
		      < best_fit->arange.high - best_fit->arange.low))
		best_fit = each_func;
	    }
	}
    }

  if (best_fit)
    {
      *functionname_ptr = best_fit->name;
      *function_ptr = best_fit;
      return TRUE;
    }
  else
    {
      return FALSE;
    }
}
