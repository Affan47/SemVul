excel_parse_name (GnmXLImporter *importer, Sheet *sheet, char *name,
		  guint8 const *expr_data, unsigned expr_len,
		  unsigned array_data_len,
		  gboolean link_to_container,
		  GnmNamedExpr *stub)
{
	GnmParsePos pp;
	GnmNamedExpr *nexpr;
	GnmExprTop const *texpr = NULL;
	char *err = NULL;

	g_return_val_if_fail (name != NULL, NULL);

	parse_pos_init (&pp, importer->wb, sheet, 0, 0);

	if (expr_len == 0) {

		texpr = gnm_expr_top_new_constant (value_new_error_NAME (NULL));
	} else {
		texpr = excel_parse_formula (&importer->container, NULL, 0, 0,
					     expr_data, expr_len,
					     array_data_len,
					     TRUE, NULL);

		if (texpr == NULL) {
			go_io_warning (importer->context, _("Failure parsing name '%s'"), name);
			texpr = gnm_expr_top_new_constant (value_new_error_REF (NULL));
		} else d (2, {
				char *tmp = gnm_expr_top_as_string
					(texpr, &pp, gnm_conventions_default);
				g_printerr ("Expression: %s\n", tmp);
				g_free (tmp);
			});
	}

	if (0 == strcmp (name, "Print_Area")) {
		GnmValue *val = gnm_expr_get_range (texpr->expr);
		if (val != NULL && val->type == VALUE_CELLRANGE) {
			GnmEvalPos ep;
			int height, width;

			if (sheet == NULL) {
				Sheet *start_sheet, *end_sheet;
				GnmRange dest;


				gnm_rangeref_normalize_pp (value_get_rangeref (val),

							   &pp,

							   &start_sheet,
							   &end_sheet,
							   &dest);
				if (start_sheet && end_sheet == start_sheet) {
					sheet = start_sheet;
					pp.sheet = sheet;
					gnm_expr_top_unref (texpr);
					texpr = gnm_expr_top_new_constant (value_new_cellrange_r (NULL, &dest));
				}
			}

			eval_pos_init_sheet (&ep, sheet);
			height = value_area_get_height (val, &ep);
			width = value_area_get_width (val, &ep);
			if (height == gnm_sheet_get_max_rows (sheet) &&
			    width == gnm_sheet_get_max_cols (sheet)) {
				gnm_expr_top_unref (texpr);
				texpr = NULL;
			}
		}
		value_release (val);


		if (texpr == NULL || gnm_expr_top_is_err (texpr, GNM_ERROR_REF)) {
			if (texpr) gnm_expr_top_unref (texpr);
			return NULL;
		}
	}

	nexpr = expr_name_add (&pp, name,
			       texpr,
			       &err, link_to_container, stub);
	if (nexpr == NULL) {
		go_io_warning (importer->context, "%s", err);
		g_free (err);
		return NULL;
	}

	return nexpr;
}
