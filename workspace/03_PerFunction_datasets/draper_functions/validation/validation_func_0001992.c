gen_wkday (DATASET *dset)
{
    char datestr[OBSLEN];
    int i, t;

    if (!dated_daily_data(dset)) {
	return E_PDWRONG;
    }

    i = series_index(dset, "weekday");

    if (i == dset->v && dataset_add_series(dset, 1)) {
	return E_ALLOC;
    }

    strcpy(dset->varname[i], "weekday");
    series_set_label(dset, i, _("day of week (1 = Monday)"));

    for (t=0; t<dset->n; t++) {
	ntodate(datestr, t, dset);
	dset->Z[i][t] = weekday_from_date(datestr);
    }

    return 0;
}
