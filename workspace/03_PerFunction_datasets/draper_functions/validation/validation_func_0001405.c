float4_accum(PG_FUNCTION_ARGS)
{
	ArrayType  *transarray = PG_GETARG_ARRAYTYPE_P(0);
	float4		newval4 = PG_GETARG_FLOAT4(1);
	float8	   *transvalues;
	float8		N,
				sumX,
				sumX2,
				newval;

	transvalues = check_float8_array(transarray, "float4_accum", 3);
	N = transvalues[0];
	sumX = transvalues[1];
	sumX2 = transvalues[2];


	newval = newval4;

	N += 1.0;
	sumX += newval;
	sumX2 += newval * newval;


	if (fcinfo->context && IsA(fcinfo->context, AggState))
	{
		transvalues[0] = N;
		transvalues[1] = sumX;
		transvalues[2] = sumX2;

		PG_RETURN_ARRAYTYPE_P(transarray);
	}
	else
	{
		Datum		transdatums[3];
		ArrayType  *result;

		transdatums[0] = Float8GetDatumFast(N);
		transdatums[1] = Float8GetDatumFast(sumX);
		transdatums[2] = Float8GetDatumFast(sumX2);

		result = construct_array(transdatums, 3,
								 FLOAT8OID,
							 sizeof(float8), false  , 'd');

		PG_RETURN_ARRAYTYPE_P(result);
	}
}
