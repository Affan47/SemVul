cost_index(IndexPath *path, PlannerInfo *root,
		   IndexOptInfo *index,
		   List *indexQuals,
		   RelOptInfo *outer_rel)
{
	RelOptInfo *baserel = index->rel;
	Cost		startup_cost = 0;
	Cost		run_cost = 0;
	Cost		indexStartupCost;
	Cost		indexTotalCost;
	Selectivity indexSelectivity;
	double		indexCorrelation,
				csquared;
	Cost		min_IO_cost,
				max_IO_cost;
	Cost		cpu_per_tuple;
	double		tuples_fetched;
	double		pages_fetched;


	Assert(IsA(baserel, RelOptInfo) &&
		   IsA(index, IndexOptInfo));
	Assert(baserel->relid > 0);
	Assert(baserel->rtekind == RTE_RELATION);

	if (!enable_indexscan)
		startup_cost += disable_cost;


	OidFunctionCall8(index->amcostestimate,
					 PointerGetDatum(root),
					 PointerGetDatum(index),
					 PointerGetDatum(indexQuals),
					 PointerGetDatum(outer_rel),
					 PointerGetDatum(&indexStartupCost),
					 PointerGetDatum(&indexTotalCost),
					 PointerGetDatum(&indexSelectivity),
					 PointerGetDatum(&indexCorrelation));


	path->indextotalcost = indexTotalCost;
	path->indexselectivity = indexSelectivity;


	startup_cost += indexStartupCost;
	run_cost += indexTotalCost - indexStartupCost;


	tuples_fetched = clamp_row_est(indexSelectivity * baserel->tuples);


	if (outer_rel != NULL && outer_rel->rows > 1)
	{


		double		num_scans = outer_rel->rows;

		pages_fetched = index_pages_fetched(tuples_fetched * num_scans,
											baserel->pages,
											(double) index->pages,
											root);

		max_IO_cost = (pages_fetched * random_page_cost) / num_scans;


		pages_fetched = ceil(indexSelectivity * (double) baserel->pages);

		pages_fetched = index_pages_fetched(pages_fetched * num_scans,
											baserel->pages,
											(double) index->pages,
											root);

		min_IO_cost = (pages_fetched * random_page_cost) / num_scans;
	}
	else
	{


		pages_fetched = index_pages_fetched(tuples_fetched,
											baserel->pages,
											(double) index->pages,
											root);


		max_IO_cost = pages_fetched * random_page_cost;


		pages_fetched = ceil(indexSelectivity * (double) baserel->pages);
		min_IO_cost = random_page_cost;
		if (pages_fetched > 1)
			min_IO_cost += (pages_fetched - 1) * seq_page_cost;
	}


	csquared = indexCorrelation * indexCorrelation;

	run_cost += max_IO_cost + csquared * (min_IO_cost - max_IO_cost);


	startup_cost += baserel->baserestrictcost.startup;
	cpu_per_tuple = cpu_tuple_cost + baserel->baserestrictcost.per_tuple;

	if (outer_rel == NULL)
	{
		QualCost	index_qual_cost;

		cost_qual_eval(&index_qual_cost, indexQuals);

		cpu_per_tuple -= index_qual_cost.per_tuple;
	}

	run_cost += cpu_per_tuple * tuples_fetched;

	path->path.startup_cost = startup_cost;
	path->path.total_cost = startup_cost + run_cost;
}
