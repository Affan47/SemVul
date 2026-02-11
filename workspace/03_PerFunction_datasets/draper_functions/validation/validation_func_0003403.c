gnumeric_randnorm (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	gnm_float mean  = value_get_as_float (argv[0]);
	gnm_float stdev = value_get_as_float (argv[1]);

	if (stdev < 0)
		return value_new_error_NUM (ei->pos);

        return value_new_float (stdev * random_normal () + mean);
}
