eval_windowfunction(WindowAggState *winstate, WindowStatePerFunc perfuncstate,
					Datum *result, bool *isnull)
{
	FunctionCallInfoData fcinfo;
	MemoryContext oldContext;

	oldContext = MemoryContextSwitchTo(winstate->ss.ps.ps_ExprContext->ecxt_per_tuple_memory);


	InitFunctionCallInfoData(fcinfo, &(perfuncstate->flinfo),
							 perfuncstate->numArguments,
							 (void *) perfuncstate->winobj, NULL);

	memset(fcinfo.argnull, true, perfuncstate->numArguments);

	*result = FunctionCallInvoke(&fcinfo);
	*isnull = fcinfo.isnull;


	if (!perfuncstate->resulttypeByVal && !fcinfo.isnull &&
		!MemoryContextContains(CurrentMemoryContext,
							   DatumGetPointer(*result)))
		*result = datumCopy(*result,
							perfuncstate->resulttypeByVal,
							perfuncstate->resulttypeLen);

	MemoryContextSwitchTo(oldContext);
}
