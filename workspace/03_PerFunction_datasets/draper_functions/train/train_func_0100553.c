gretl_list_array_new (int nlists, int nterms)
{
    int **lists = NULL;
    int i;

    if (nlists < 0) {
	return NULL;
    }

    lists = malloc(nlists * sizeof *lists);

    if (lists != NULL) {
	for (i=0; i<nlists; i++) {
	    lists[i] = gretl_list_new(nterms);
	}
    }

    return lists;
}
