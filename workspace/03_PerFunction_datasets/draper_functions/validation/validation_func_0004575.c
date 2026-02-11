search(int max_constrained, int depth)
{
  int id;
  BOOL go;
  int rc = check_time_memory();
  if (rc != SEARCH_GO_NO_MODELS)
    return rc;
  else {
    id = select_cell(max_constrained);
    if (id == -1) {
      rc = possible_model();
      return rc;
    }
    else {
      int i, last;
      int x = Cells[id].max_index;
      max_constrained = MAX(max_constrained, x);
      Mstats.selections++;

      if (flag(Opt->trace)) {
	printf("select: ");
	p_model(FALSE);

      }

      if (Cells[id].symbol->type == RELATION)
	last = 1;
      else if (flag(Opt->lnh))
	last = MIN(max_constrained+1, Domain_size-1);
      else
	last = Domain_size-1;

      for (i = 0, go = TRUE; i <= last && go; i++) {
	Estack stk;
	Mstats.assignments++;

	if (flag(Opt->trace)) {
	  printf("assign: ");
	  fwrite_term(stdout, Cells[id].eterm);
	  printf("=%d (%d) depth=%d\n", i, last, depth);
	}

	stk = assign_and_propagate(id, Domain[i]);

	if (stk != NULL) {

	  rc = search(MAX(max_constrained, i), depth+1);

	  restore_from_stack(stk);
	  if (rc == SEARCH_GO_MODELS)
	    go = mace4_skolem_check(id);
	  else
	    go = (rc == SEARCH_GO_NO_MODELS);
	}
      }
      return rc;
    }
  }
}
