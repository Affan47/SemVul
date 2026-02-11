alloc_array_range_semnode_real()
{
    Array_range_semnode *ars;

    ars = (Array_range_semnode *)calloc(1, sizeof(Array_range_semnode));
    if (ars == NULL) {
	fatal("mem error\n");
    }
    ars->lower = NULL;
    ars->upper = NULL;
    ars->step = NULL;

    ars->lower_tree = NULL;
    ars->upper_tree = NULL;
    ars->step_tree = NULL;

    ars->next_dim = NULL;
    ars->unknown = FALSE;

    return ars;
}
