date_maj_min (int t, const DATASET *dset, int *maj, int *min)
{
    char obs[OBSLEN];

    ntodate(obs, t, dset);

    if (maj != NULL) {
	*maj = atoi(obs);
    }

    if (min != NULL) {
	char *s = strchr(obs, ':');

	if (s != NULL && strlen(s) > 1) {
	    *min = atoi(s + 1);
	} else {
	    *min = 1;
	}
    }
}
