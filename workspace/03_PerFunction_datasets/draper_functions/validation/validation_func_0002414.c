score_the_part(int *p,
			   int n,
			   struct clause *c,
			   int *bp,
			   int *bs)
{
  int vars_1[MAX_VARS], vars_2[MAX_VARS];
  int vars_union[MAX_VARS], vars_intersection[MAX_VARS];
  int nvars = biggest_var_clause(c) + 1;
  int i, card_intersection;

  for (i = 0; i < MAX_VARS; i++)
    vars_1[i] = vars_2[i] = 0;

  which_vars_part(vars_1, c, p, 0);
  which_vars_part(vars_2, c, p, 1);

  union_vars(vars_1, vars_2, nvars, vars_union);
  intersect_vars(vars_1, vars_2, nvars, vars_intersection);
  card_intersection = cardinality(vars_intersection, nvars);

  if (card_intersection <= MAX_ARITY) {
    int c1 = cardinality(vars_1, nvars);
    int c2 = cardinality(vars_2, nvars);

    int diff1 = diff_cardinality(vars_union, vars_1, nvars);
    int diff2 = diff_cardinality(vars_union, vars_2, nvars);

    if (diff1 > 0 && diff2 > 0) {


      int score = (MAX(c1,c2) * 100) + card_intersection;
      if (score < *bs) {
	*bs = score;
	for (i = 0; i < n; i++)
	  bp[i] = p[i];
      }
    }
  }
}
