filter_suitable_components (struct loop *loop, struct component *comps)
{
  struct component **comp, *act;

  for (comp = &comps; *comp; )
    {
      act = *comp;
      if (suitable_component_p (loop, act))
	comp = &act->next;
      else
	{
	  dref ref;
	  unsigned i;

	  *comp = act->next;
	  FOR_EACH_VEC_ELT (act->refs, i, ref)
	    free (ref);
	  release_component (act);
	}
    }

  return comps;
}
