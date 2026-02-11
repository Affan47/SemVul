cut_extra_caller_array_du_semnode(Array_def_use_table_semnode *du_head,
				  const int entry,
				  const symbol_kind kind,
				  int array_dim)
{
    Array_def_use_table_semnode *apt;

    for( apt = du_head; apt != NULL; apt = apt->next) {
        if (apt->entry == entry
	    && apt->kind == kind) {
            cut_extra_caller_array_rl_semnode(apt, array_dim);
            return;
        }
    }
}
