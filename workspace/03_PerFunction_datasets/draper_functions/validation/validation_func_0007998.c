get_var_table(Var_table **var_head, int entry)
{
    Var_table	*vpt;

    vpt = search_var_table(*var_head, entry);
    if (vpt == NULL) {
	vpt = alloc_var_table();
	vpt->entry = entry;
	append_var_table(var_head, vpt);
    }
    return(vpt);
}
