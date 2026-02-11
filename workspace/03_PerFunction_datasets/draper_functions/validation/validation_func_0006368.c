cb_auto_expr_cell_changed (GtkWidget *item, WBCGtk *wbcg)
{
	WorkbookView *wbv = wb_control_view (WORKBOOK_CONTROL (wbcg));
	const GnmEvalPos *ep;
	GnmExprTop const *texpr;
	GnmValue const *v;

	if (wbcg->updating_ui)
		return;

	ep = g_object_get_data (G_OBJECT (item), "evalpos");

	g_object_set (wbv,
		      "auto-expr-func", NULL,
		      "auto-expr-descr", NULL,
		      "auto-expr-eval-pos", ep,
		      NULL);


	texpr = wbv->auto_expr.dep.texpr;
	v = gnm_expr_top_get_constant (texpr);
	if (v)
		g_object_set (wbv,
			      "auto-expr-descr", value_peek_string (v),
			      NULL);
}
