get_corrgm_matrix (NODE *l,
					NODE *m,
					NODE *r,
					parser *p)
{
    int xcf = (r->t != EMPTY);
    int *list = NULL;
    gretl_matrix *A = NULL;
    int k;


    k = node_get_int(m, p);
    if (p->err) {
	return NULL;
    }


    if (l->t != VEC && l->t != MAT) {
	list = node_get_list(l, p);
	if (p->err) {
	    return NULL;
	}
    }


    if (r->t == MAT) {
	if (r->v.m->cols != 1) {
	    p->err = E_NONCONF;
	    return NULL;
	}
    }

    if (!xcf) {

	if (l->t == VEC) {
	    A = acf_matrix(l->v.xvec, k, p->dset, 0, &p->err);
	} else if (l->t == MAT) {
	    A = multi_acf(l->v.m, NULL, NULL, k, &p->err);
	} else {

	    A = multi_acf(NULL, list, p->dset, k, &p->err);
	}
    } else {

	void *px = NULL, *py = NULL;
	int xtype = VEC;

	if (list != NULL) {
	    px = list;
	    xtype = LIST;
	} else if (l->t == MAT) {
	    px = l->v.m;
	    xtype = MAT;
	} else {
	    px = l->v.xvec;
	}

	py = (r->t == MAT)? (void *) r->v.m : (void *) r->v.xvec;

	A = multi_xcf(px, xtype, py, r->t, p->dset, k, &p->err);
    }

    free(list);

    return A;
}
