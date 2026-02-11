op_precalc_1 (GelETree *n,
	      void (*func)(mpw_ptr,mpw_ptr),
	      gboolean respect_type)
{
	GelETree *l;
	mpw_t res;
	GEL_GET_L(n,l);
	if (l->type != GEL_VALUE_NODE ||
	    (respect_type &&
	     (mpw_is_complex (l->val.value) ||
	      mpw_is_real_part_float (l->val.value))))
		return;
	mpw_init(res);
	(*func)(res,l->val.value);
	if G_UNLIKELY (gel_error_num) {
		mpw_clear(res);
		gel_error_num = GEL_NO_ERROR;
		return;
	}
	freetree_full(n,TRUE,FALSE);
	gel_makenum_use_from(n,res);
}
