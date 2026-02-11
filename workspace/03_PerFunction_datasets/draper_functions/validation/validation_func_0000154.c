plotgroup_factor_setup (PLOTGROUP *grp,
				   const DATASET *dset)
{
    int T = sample_size(dset);
    int dv = grp->list[2];
    int err = 0;

    grp->dvals = gretl_matrix_values(dset->Z[dv] + dset->t1, T,
				     OPT_S, &err);
    if (!err) {
	grp->nplots = gretl_vector_get_length(grp->dvals);
    }

    return err;
}
