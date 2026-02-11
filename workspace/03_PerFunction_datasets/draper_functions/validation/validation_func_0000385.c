int4_numeric(PG_FUNCTION_ARGS)
{
	int32		val = PG_GETARG_INT32(0);
	Numeric		res;
	NumericVar	result;

	init_var(&result);

	int8_to_numericvar((int64) val, &result);

	res = make_result(&result);

	free_var(&result);

	PG_RETURN_NUMERIC(res);
}
