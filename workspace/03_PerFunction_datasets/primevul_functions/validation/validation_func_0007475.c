duplicate_node_closure (re_dfa_t *dfa, Idx top_org_node, Idx top_clone_node,
			Idx root_node, unsigned int init_constraint)
{
  Idx org_node, clone_node;
  bool ok;
  unsigned int constraint = init_constraint;
  for (org_node = top_org_node, clone_node = top_clone_node;;)
    {
      Idx org_dest, clone_dest;
      if (dfa->nodes[org_node].type == OP_BACK_REF)
	{


	  org_dest = dfa->nexts[org_node];
	  re_node_set_empty (dfa->edests + clone_node);
	  clone_dest = duplicate_node (dfa, org_dest, constraint);
	  if (BE (clone_dest == REG_MISSING, 0))
	    return REG_ESPACE;
	  dfa->nexts[clone_node] = dfa->nexts[org_node];
	  ok = re_node_set_insert (dfa->edests + clone_node, clone_dest);
	  if (BE (! ok, 0))
	    return REG_ESPACE;
	}
      else if (dfa->edests[org_node].nelem == 0)
	{


	  dfa->nexts[clone_node] = dfa->nexts[org_node];
	  break;
	}
      else if (dfa->edests[org_node].nelem == 1)
	{


	  org_dest = dfa->edests[org_node].elems[0];
	  re_node_set_empty (dfa->edests + clone_node);


	  if (org_node == root_node && clone_node != org_node)
	    {
	      ok = re_node_set_insert (dfa->edests + clone_node, org_dest);
	      if (BE (! ok, 0))
	        return REG_ESPACE;
	      break;
	    }

	  constraint |= dfa->nodes[org_node].constraint;
	  clone_dest = duplicate_node (dfa, org_dest, constraint);
	  if (BE (clone_dest == REG_MISSING, 0))
	    return REG_ESPACE;
	  ok = re_node_set_insert (dfa->edests + clone_node, clone_dest);
	  if (BE (! ok, 0))
	    return REG_ESPACE;
	}
      else
	{


	  org_dest = dfa->edests[org_node].elems[0];
	  re_node_set_empty (dfa->edests + clone_node);

	  clone_dest = search_duplicated_node (dfa, org_dest, constraint);
	  if (clone_dest == REG_MISSING)
	    {

	      reg_errcode_t err;
	      clone_dest = duplicate_node (dfa, org_dest, constraint);
	      if (BE (clone_dest == REG_MISSING, 0))
		return REG_ESPACE;
	      ok = re_node_set_insert (dfa->edests + clone_node, clone_dest);
	      if (BE (! ok, 0))
		return REG_ESPACE;
	      err = duplicate_node_closure (dfa, org_dest, clone_dest,
					    root_node, constraint);
	      if (BE (err != REG_NOERROR, 0))
		return err;
	    }
	  else
	    {


	      ok = re_node_set_insert (dfa->edests + clone_node, clone_dest);
	      if (BE (! ok, 0))
		return REG_ESPACE;
	    }

	  org_dest = dfa->edests[org_node].elems[1];
	  clone_dest = duplicate_node (dfa, org_dest, constraint);
	  if (BE (clone_dest == REG_MISSING, 0))
	    return REG_ESPACE;
	  ok = re_node_set_insert (dfa->edests + clone_node, clone_dest);
	  if (BE (! ok, 0))
	    return REG_ESPACE;
	}
      org_node = org_dest;
      clone_node = clone_dest;
    }
  return REG_NOERROR;
}
