gnumeric_r_dsnorm (GnmFuncEvalInfo *ei, GnmValue const * const *args)
{
	gnm_float x = value_get_as_float (args[0]);
	gnm_float shape = value_get_as_float (args[1]);
	gnm_float location = value_get_as_float (args[2]);
	gnm_float scale = value_get_as_float (args[3]);
	gboolean give_log = args[4] ? value_get_as_checked_bool (args[4]) : FALSE;

	return value_new_float (dsnorm (x, shape, location, scale, give_log));
}
