need_fake_edge_p (gimple t)
{
  tree fndecl = NULL_TREE;
  int call_flags = 0;


  if (is_gimple_call (t))
    {
      fndecl = gimple_call_fndecl (t);
      call_flags = gimple_call_flags (t);
    }

  if (is_gimple_call (t)
      && fndecl
      && DECL_BUILT_IN (fndecl)
      && (call_flags & ECF_NOTHROW)
      && !(call_flags & ECF_RETURNS_TWICE)


      && !(DECL_BUILT_IN_CLASS (fndecl) == BUILT_IN_NORMAL
	   && DECL_FUNCTION_CODE (fndecl) == BUILT_IN_FORK))
    return false;

  if (is_gimple_call (t))
    {
      edge_iterator ei;
      edge e;
      basic_block bb;

      if (!(call_flags & ECF_NORETURN))
	return true;

      bb = gimple_bb (t);
      FOR_EACH_EDGE (e, ei, bb->succs)
	if ((e->flags & EDGE_FAKE) == 0)
	  return true;
    }

  if (gimple_code (t) == GIMPLE_ASM
       && (gimple_asm_volatile_p (t) || gimple_asm_input_p (t)))
    return true;

  return false;
}
