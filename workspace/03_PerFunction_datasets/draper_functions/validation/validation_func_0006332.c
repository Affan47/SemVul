gnm_solver_constraint_get_part (GnmSolverConstraint const *c,
				GnmSolverParameters const *sp, int i,
				GnmCell **lhs, gnm_float *cl,
				GnmCell **rhs, gnm_float *cr)
{
	GnmSheetRange sr;
	int h, w, dx, dy;
	GnmValue const *vl, *vr;

	if (cl)	*cl = 0;
	if (cr)	*cr = 0;
	if (lhs) *lhs = NULL;
	if (rhs) *rhs = NULL;

	if (!gnm_solver_constraint_valid (c, sp))
		return FALSE;

	vl = gnm_solver_constraint_get_lhs (c);
	vr = gnm_solver_constraint_get_rhs (c);

	gnm_sheet_range_from_value (&sr, vl);
	w = range_width (&sr.range);
	h = range_height (&sr.range);

	dy = i / w;
	dx = i % w;
	if (dy >= h)
		return FALSE;

	if (lhs)
		*lhs = sheet_cell_get (eval_sheet (sr.sheet, sp->sheet),
				       sr.range.start.col + dx,
				       sr.range.start.row + dy);

	if (!gnm_solver_constraint_has_rhs (c)) {

	} else if (VALUE_IS_FLOAT (vr)) {
		if (cr)
			*cr = value_get_as_float (vr);
	} else {
		gnm_sheet_range_from_value (&sr, vr);
		if (rhs)
			*rhs = sheet_cell_get (eval_sheet (sr.sheet, sp->sheet),
					       sr.range.start.col + dx,
					       sr.range.start.row + dy);
	}

	return TRUE;
}
