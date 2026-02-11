box_stats_leader (PLOTGROUP *grp, int i, int offset,
			      PRN *prn)
{
    BOXPLOT *plt = &grp->plots[i];

    if (factorized(grp)) {
	char numstr[32];

	sprintf(numstr, "%g", gretl_vector_get(grp->dvals, i));
	pprintf(prn, "%-*s", offset, numstr);
    } else if (plt->bool != NULL) {
	pprintf(prn, "%s\n %-*s", plt->varname, offset - 1, plt->bool);
    } else {
	pprintf(prn, "%-*s", offset, plt->varname);
    }
}
