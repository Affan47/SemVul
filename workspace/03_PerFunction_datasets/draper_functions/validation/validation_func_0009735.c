applicable_toms513(const problem_rdft *p, planner *plnr,
			   int dim0, int dim1, int dim2, INT *nbuf)
{
     INT n = p->vecsz->dims[dim0].n;
     INT m = p->vecsz->dims[dim1].n;
     INT vl, vs;
     get_transpose_vec(p, dim2, &vl, &vs);
     *nbuf = 2*vl
	  + ((n + m) / 2 * sizeof(char) + sizeof(R) - 1) / sizeof(R);
     return (!NO_SLOWP(plnr)
	     && (vl > 8 || !NO_UGLYP(plnr))
	     && n != m
	     && Ntuple_transposable(p->vecsz->dims + dim0,
				    p->vecsz->dims + dim1,
				    vl, vs));
}
