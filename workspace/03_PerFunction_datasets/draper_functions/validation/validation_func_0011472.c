dpow(PG_FUNCTION_ARGS)
{
	float8		arg1 = PG_GETARG_FLOAT8(0);
	float8		arg2 = PG_GETARG_FLOAT8(1);
	float8		result;


	if (arg1 == 0 && arg2 < 0)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_ARGUMENT_FOR_POWER_FUNCTION),
				 errmsg("zero raised to a negative power is undefined")));
	if (arg1 < 0 && floor(arg2) != arg2)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_ARGUMENT_FOR_POWER_FUNCTION),
				 errmsg("a negative number raised to a non-integer power yields a complex result")));


	errno = 0;
	result = pow(arg1, arg2);
	if (errno == EDOM && isnan(result))
	{
		if ((fabs(arg1) > 1 && arg2 >= 0) || (fabs(arg1) < 1 && arg2 < 0))

			result = get_float8_infinity();
		else if (fabs(arg1) != 1)
			result = 0;
		else
			result = 1;
	}
	else if (errno == ERANGE && result != 0 && !isinf(result))
		result = get_float8_infinity();

	CHECKFLOATVAL(result, isinf(arg1) || isinf(arg2), arg1 == 0);
	PG_RETURN_FLOAT8(result);
}
