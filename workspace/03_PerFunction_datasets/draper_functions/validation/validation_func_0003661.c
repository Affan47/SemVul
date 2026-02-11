TrimPoly_op(GelCtx *ctx, GelETree * * a, gboolean *exception)
{
	GelETree *n;

	if G_UNLIKELY ( ! check_poly(a,1,"TrimPoly",TRUE))
		return NULL;

	GEL_GET_NEW_NODE(n);
	n->type = GEL_MATRIX_NODE;
	n->mat.matrix = gel_matrixw_copy(a[0]->mat.matrix);
	n->mat.quoted = FALSE;

	poly_cut_zeros(n->mat.matrix);

	return n;
}
