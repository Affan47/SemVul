gnumeric_error_type (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	switch (value_error_classify (argv[0])) {
	case GNM_ERROR_NULL: return value_new_int (1);
	case GNM_ERROR_DIV0: return value_new_int (2);
	case GNM_ERROR_VALUE: return value_new_int (3);
	case GNM_ERROR_REF: return value_new_int (4);
	case GNM_ERROR_NAME: return value_new_int (5);
	case GNM_ERROR_NUM: return value_new_int (6);
	case GNM_ERROR_NA: return value_new_int (7);
	default:
		return value_new_error_NA (ei->pos);
	}
}
