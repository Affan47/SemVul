cost_agg(Path *path, PlannerInfo *root,
		 AggStrategy aggstrategy, const AggClauseCosts *aggcosts,
		 int numGroupCols, double numGroups,
		 Cost input_startup_cost, Cost input_total_cost,
		 double input_tuples)
{
	double		output_tuples;
	Cost		startup_cost;
	Cost		total_cost;
	AggClauseCosts dummy_aggcosts;


	if (aggcosts == NULL)
	{
		Assert(aggstrategy == AGG_HASHED);
		MemSet(&dummy_aggcosts, 0, sizeof(AggClauseCosts));
		aggcosts = &dummy_aggcosts;
	}


	if (aggstrategy == AGG_PLAIN)
	{
		startup_cost = input_total_cost;
		startup_cost += aggcosts->transCost.startup;
		startup_cost += aggcosts->transCost.per_tuple * input_tuples;
		startup_cost += aggcosts->finalCost;

		total_cost = startup_cost + cpu_tuple_cost;
		output_tuples = 1;
	}
	else if (aggstrategy == AGG_SORTED)
	{

		startup_cost = input_startup_cost;
		total_cost = input_total_cost;

		total_cost += aggcosts->transCost.startup;
		total_cost += aggcosts->transCost.per_tuple * input_tuples;
		total_cost += (cpu_operator_cost * numGroupCols) * input_tuples;
		total_cost += aggcosts->finalCost * numGroups;
		total_cost += cpu_tuple_cost * numGroups;
		output_tuples = numGroups;
	}
	else
	{

		startup_cost = input_total_cost;
		startup_cost += aggcosts->transCost.startup;
		startup_cost += aggcosts->transCost.per_tuple * input_tuples;
		startup_cost += (cpu_operator_cost * numGroupCols) * input_tuples;
		total_cost = startup_cost;
		total_cost += aggcosts->finalCost * numGroups;
		total_cost += cpu_tuple_cost * numGroups;
		output_tuples = numGroups;
	}

	path->rows = output_tuples;
	path->startup_cost = startup_cost;
	path->total_cost = total_cost;
}
