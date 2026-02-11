list_delete_oid(List *list, Oid datum)
{
	ListCell   *cell;
	ListCell   *prev;

	Assert(IsOidList(list));
	check_list_invariants(list);

	prev = NULL;
	foreach(cell, list)
	{
		if (lfirst_oid(cell) == datum)
			return list_delete_cell(list, cell, prev);

		prev = cell;
	}


	return list;
}
