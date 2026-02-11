gel_matrixw_new_with_matrix_value_only_real_nonrational (GelMatrix *mat)
{
	GelMatrixW *m;
	NEW_MATRIX (m);
#ifdef MATRIX_DEBUG
	printf ("%s\n", G_GNUC_PRETTY_FUNCTION);
#endif

	m->m = mat;
	m->m->use++;

	m->cached_value_only = 1;
	m->value_only = 1;
	m->cached_value_only_real = 1;
	m->value_only_real = 1;
	m->cached_value_only_rational = 1;
	m->value_only_rational = 0;
	m->cached_value_only_integer = 1;
	m->value_only_integer = 0;
	m->cached_value_or_bool_only = 1;
	m->value_or_bool_only = 1;
	m->rref = 0;

	m->tr = 0;
	m->regx = NULL;
	m->regy = NULL;
	m->regw = m->m->width;
	m->regh = m->m->height;

	return m;
}
