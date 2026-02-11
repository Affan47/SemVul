set_base_rel_pathlists(PlannerInfo *root)
{
	Index		rti;

	for (rti = 1; rti < root->simple_rel_array_size; rti++)
	{
		RelOptInfo *rel = root->simple_rel_array[rti];


		if (rel == NULL)
			continue;

		Assert(rel->relid == rti);


		if (rel->reloptkind != RELOPT_BASEREL)
			continue;

		set_rel_pathlist(root, rel, rti);
	}
}
