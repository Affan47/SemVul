gnm_dep_style_dependency (Sheet *sheet,
			  GnmExprTop const *texpr,
			  GnmRange const *r,
			  GPtrArray *accum)
{
	int row, col;


	for (row = r->start.row; row <= r->end.row; row++) {
		for (col = r->start.col; col <= r->end.col; col++) {
			GnmStyleDependent *sd = g_new0 (GnmStyleDependent, 1);
			GnmDependent *dep = &sd->base;

			dep->sheet = sheet;
			dep->flags = DEPENDENT_STYLE;
			dep->texpr = NULL;
			sd->pos.col = col;
			sd->pos.row = row;

			dependent_set_expr (dep, texpr);
			dependent_link (dep);
			g_ptr_array_add (accum, dep);
		}
	}
}
