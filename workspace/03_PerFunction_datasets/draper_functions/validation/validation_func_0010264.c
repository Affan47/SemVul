tintervalsame(PG_FUNCTION_ARGS)
{
	TimeInterval i1 = PG_GETARG_TIMEINTERVAL(0);
	TimeInterval i2 = PG_GETARG_TIMEINTERVAL(1);

	if (i1->status == T_INTERVAL_INVAL || i2->status == T_INTERVAL_INVAL)
		PG_RETURN_BOOL(false);

	if (DatumGetBool(DirectFunctionCall2(abstimeeq,
										 AbsoluteTimeGetDatum(i1->data[0]),
									   AbsoluteTimeGetDatum(i2->data[0]))) &&
		DatumGetBool(DirectFunctionCall2(abstimeeq,
										 AbsoluteTimeGetDatum(i1->data[1]),
										 AbsoluteTimeGetDatum(i2->data[1]))))
		PG_RETURN_BOOL(true);
	PG_RETURN_BOOL(false);
}
