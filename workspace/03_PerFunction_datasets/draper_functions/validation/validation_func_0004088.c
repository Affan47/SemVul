cvs_branch_parent (cvs_file *f, cvs_number *branch)

{
    cvs_number	n;
    cvs_version	*v;

    n = *branch;
    n.n[n.c-1] = 0;
    for (v = f->versions; v; v = v->next) {
	if (cvs_same_branch (&n, &v->number) &&
	    cvs_number_compare (branch, &v->number) < 0 &&
	    cvs_number_compare (&n, &v->number) >= 0)
	    n = v->number;
    }
    return n;
}
