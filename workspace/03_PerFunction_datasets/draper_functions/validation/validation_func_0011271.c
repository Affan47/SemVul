ExecAssignResultTypeFromTL(PlanState *planstate)
{
	bool		hasoid;
	TupleDesc	tupDesc;

	if (ExecContextForcesOids(planstate, &hasoid))
	{

	}
	else
	{

		hasoid = false;
	}


	tupDesc = ExecTypeFromTL(planstate->plan->targetlist, hasoid);
	ExecAssignResultType(planstate, tupDesc);
}
