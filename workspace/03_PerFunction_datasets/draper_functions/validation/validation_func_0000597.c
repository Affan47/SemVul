class_constr_state_get_cur(const qpol_iterator_t * iter)
{
	class_constr_state_t *ccs = NULL;
	qpol_constraint_t *qc = NULL;

	if (!iter || !(ccs = (class_constr_state_t *) qpol_iterator_state(iter)) || qpol_iterator_end(iter)) {
		errno = EINVAL;
		return NULL;
	}

	if (!(qc = calloc(1, sizeof(qpol_constraint_t)))) {
		return NULL;
	}
	qc->obj_class = ccs->obj_class;
	qc->constr = ccs->cur;

	return qc;
}
