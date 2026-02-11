ast_graft_list_fuse(
	__isl_take isl_ast_graft_list *list, __isl_keep isl_ast_build *build,
	__isl_keep isl_ast_build *sub_build, int up)
{
	isl_ctx *ctx;
	isl_ast_node *node;
	isl_ast_graft *graft;
	isl_ast_node_list *node_list;
	isl_set *guard;

	if (!list)
		return NULL;

	ctx = isl_ast_build_get_ctx(build);
	guard = extract_hoistable_guard(list, build);
	list = gist_guards(list, guard);
	list = insert_pending_guard_nodes(list, sub_build);

	node_list = extract_node_list(list);
	node = isl_ast_node_from_ast_node_list(node_list);

	graft = isl_ast_graft_alloc(node, build);

	if (!up || isl_options_get_ast_build_exploit_nested_bounds(ctx)) {
		isl_basic_set *enforced;
		enforced = extract_shared_enforced(list, build);
		graft = isl_ast_graft_enforce(graft, enforced);
	}

	graft = store_guard(graft, guard, build);

	isl_ast_graft_list_free(list);
	return graft;
}
