applicable_tiled(const P *pln, const problem_rdft *p)
{
     return (1
	     && p->I != p->O
	     && pln->rnk >= 2


	     && X(compute_tilesz)(pln->vl, 1) > 4
	  );
}
