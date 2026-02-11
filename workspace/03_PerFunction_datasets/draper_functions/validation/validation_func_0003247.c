post_visit (Sym *parent)
{
  Sym *member;

  DBG (DFNDEBUG, printf ("[post_visit]\t%d: ", dfn_depth);
       print_name (parent);
       printf ("\n"));


  if (parent->cg.cyc.head == parent)
    {
      ++dfn_counter;
      for (member = parent; member; member = member->cg.cyc.next)
	{
	  member->cg.top_order = dfn_counter;
	  DBG (DFNDEBUG, printf ("[post_visit]\t\tmember ");
	       print_name (member);
	       printf ("-> cg.top_order = %d\n", dfn_counter));
	}
    }
  else
    {
      DBG (DFNDEBUG, printf ("[post_visit]\t\tis part of a cycle\n"));
    }
  --dfn_depth;
}
