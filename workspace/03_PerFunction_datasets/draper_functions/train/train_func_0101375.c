isl_qpolynomial_fold_realign_domain(
	__isl_take isl_qpolynomial_fold *fold, __isl_take isl_reordering *r)
{
	int i;

	fold = isl_qpolynomial_fold_cow(fold);
	if (!fold || !r)
		goto error;

	for (i = 0; i < fold->n; ++i) {
		fold->qp[i] = isl_qpolynomial_realign_domain(fold->qp[i],
						    isl_reordering_copy(r));
		if (!fold->qp[i])
			goto error;
	}

	fold = isl_qpolynomial_fold_reset_domain_space(fold,
						    isl_space_copy(r->dim));

	isl_reordering_free(r);

	return fold;
error:
	isl_qpolynomial_fold_free(fold);
	isl_reordering_free(r);
	return NULL;
}
