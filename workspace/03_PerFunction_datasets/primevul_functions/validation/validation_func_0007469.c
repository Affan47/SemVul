calc_eclosure_iter (re_node_set *new_set, re_dfa_t *dfa, Idx node, bool root)
{
  reg_errcode_t err;
  Idx i;
  re_node_set eclosure;
  bool ok;
  bool incomplete = false;
  err = re_node_set_alloc (&eclosure, dfa->edests[node].nelem + 1);
  if (BE (err != REG_NOERROR, 0))
    return err;


  dfa->eclosures[node].nelem = REG_MISSING;


  if (dfa->nodes[node].constraint
      && dfa->edests[node].nelem
      && !dfa->nodes[dfa->edests[node].elems[0]].duplicated)
    {
      err = duplicate_node_closure (dfa, node, node, node,
				    dfa->nodes[node].constraint);
      if (BE (err != REG_NOERROR, 0))
	return err;
    }


  if (IS_EPSILON_NODE(dfa->nodes[node].type))
    for (i = 0; i < dfa->edests[node].nelem; ++i)
      {
	re_node_set eclosure_elem;
	Idx edest = dfa->edests[node].elems[i];


	if (dfa->eclosures[edest].nelem == REG_MISSING)
	  {
	    incomplete = true;
	    continue;
	  }


	if (dfa->eclosures[edest].nelem == 0)
	  {
	    err = calc_eclosure_iter (&eclosure_elem, dfa, edest, false);
	    if (BE (err != REG_NOERROR, 0))
	      return err;
	  }
	else
	  eclosure_elem = dfa->eclosures[edest];

	err = re_node_set_merge (&eclosure, &eclosure_elem);
	if (BE (err != REG_NOERROR, 0))
	  return err;


	if (dfa->eclosures[edest].nelem == 0)
	  {
	    incomplete = true;
	    re_node_set_free (&eclosure_elem);
	  }
      }


  ok = re_node_set_insert (&eclosure, node);
  if (BE (! ok, 0))
    return REG_ESPACE;
  if (incomplete && !root)
    dfa->eclosures[node].nelem = 0;
  else
    dfa->eclosures[node] = eclosure;
  *new_set = eclosure;
  return REG_NOERROR;
}
