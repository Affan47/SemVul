get_dataset_t (const double *x, int pos, int t1)
{
    int t, k = 0;

    for (t=t1; k<=pos; t++) {
	if (!xna(x[t])) {
	    if (k == pos) {
		return t;
	    }
	    k++;
	}
    }

    return 0;
}
