gnm_go_data_matrix_get_str (GODataMatrix *dat, unsigned i, unsigned j)
{
	GnmGODataMatrix *mat = (GnmGODataMatrix *)dat;
	GnmEvalPos ep;
	GOFormat const *fmt = NULL;

	if (mat->val == NULL)
		gnm_go_data_matrix_load_size (dat);
	g_return_val_if_fail (mat->val != NULL, NULL);

	eval_pos_init_dep (&ep, &mat->dep);
	return render_val (mat->val, i, j, fmt, &ep);
}
