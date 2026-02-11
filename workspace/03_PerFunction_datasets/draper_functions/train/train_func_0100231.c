lrs_getnextbasis (lrs_dic ** D_p, lrs_dat * Q, long backtrack)


{

  long i = 0L, j = 0L;
  long m = D->m;
  long d = D->d;


  if (backtrack && D->depth == 0)
    return FALSE;

  if (Q->maxoutput > 0 && Q->count[0]+Q->count[1]-Q->hull >= Q->maxoutput)
     return FALSE;

  while ((j < d) || (D->B[m] != m))
    {
      if (D->depth >= Q->maxdepth)
	{
	  backtrack = TRUE;
	  if (Q->runs > 0)
	    lrs_estimate (D, Q);
	  if (Q->maxdepth == 0)
	    return FALSE;
	}

      if ( Q->truncate && negative(D->A[0][0]))
          backtrack = TRUE;

      if (backtrack)
	{
	  backtrack = FALSE;

	  if (check_cache (D_p, Q, &i, &j))
	    {
	      if (Q->debug)
		fprintf (lrs_ofp, "\n Cached Dict. restored to depth %ld\n", D->depth);
	    }
	  else
	    {
	      D->depth--;
	      selectpivot (D, Q, &i, &j);
	      pivot (D, Q, i, j);
	      update (D, Q, &i, &j);
	    }

	  if (Q->debug)
	    {
	      fprintf (lrs_ofp, "\n Backtrack Pivot: indices i=%ld j=%ld depth=%ld", i, j, D->depth);
	      printA (D, Q);
	    };

	  j++;
	}

      if (D->depth < Q->mindepth)
	break;


      while ((j < d) && !reverse (D, Q, &i, j))
	j++;
      if (j == d)
	backtrack = TRUE;

      else

	{
	  cache_dict (D_p, Q, i, j);


	  D->depth++;
	  if (D->depth > Q->deepest)
	    Q->deepest++;

	  pivot (D, Q, i, j);
	  update (D, Q, &i, &j);

	  D->lexflag = lexmin (D, Q, ZERO);
	  Q->count[2]++;
	  Q->totalnodes++;

	  save_basis (*D_p, Q);
	  if (Q->strace == Q->count[2])
	    Q->debug = TRUE;
	  if (Q->etrace == Q->count[2])
	    Q->debug = FALSE;
	  return TRUE;
	}


    }
  return FALSE;
}
