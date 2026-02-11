process_spec_exprs (av_set_t *av_ptr)
{
  bool try_data_p = true;
  bool try_control_p = true;
  expr_t expr;
  av_set_iterator si;

  if (spec_info == NULL)
    return;


  FOR_EACH_EXPR_1 (expr, si, av_ptr)
    {
      ds_t ds;

      ds = EXPR_SPEC_DONE_DS (expr);


      if ((ds & SPECULATIVE)
          && (ds_weak (ds) < spec_info->data_weakness_cutoff
              || EXPR_USEFULNESS (expr) < spec_info->control_weakness_cutoff
	      || (pipelining_p && false
		  && (ds & DATA_SPEC)
		  && (ds & CONTROL_SPEC))))
        {
          av_set_iter_remove (&si);
          continue;
        }

      if ((spec_info->flags & PREFER_NON_DATA_SPEC)
          && !(ds & BEGIN_DATA))
        try_data_p = false;

      if ((spec_info->flags & PREFER_NON_CONTROL_SPEC)
          && !(ds & BEGIN_CONTROL))
        try_control_p = false;
    }

  FOR_EACH_EXPR_1 (expr, si, av_ptr)
    {
      ds_t ds;

      ds = EXPR_SPEC_DONE_DS (expr);

      if (ds & SPECULATIVE)
        {
          if ((ds & BEGIN_DATA) && !try_data_p)


            av_set_iter_remove (&si);

          if ((ds & BEGIN_CONTROL) && !try_control_p)


            av_set_iter_remove (&si);
        }
    }
}
