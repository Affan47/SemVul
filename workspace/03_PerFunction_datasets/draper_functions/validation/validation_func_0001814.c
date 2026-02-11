make_du_IntSet(IntSet         src,
	       Def_use_table *du_head)
{
    Def_use_table *du_tbl = NULL;

    for(du_tbl = du_head; du_tbl != NULL; du_tbl = du_tbl->next){
	add1_IntSet(src, du_tbl->entry);
    }
}
