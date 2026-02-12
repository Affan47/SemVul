static void binder_inc_node_tmpref_ilocked(struct binder_node *node)
{


	node->tmp_refs++;
}
