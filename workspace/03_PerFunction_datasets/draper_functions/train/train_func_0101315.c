call_create_leaf(
	__isl_take isl_union_map *executed, __isl_take isl_ast_build *build)
{
	isl_set *guard;
	isl_ast_node *node;
	isl_ast_graft *graft;
	isl_ast_build *user_build;

	guard = isl_ast_build_get_pending(build);
	user_build = isl_ast_build_copy(build);
	user_build = isl_ast_build_replace_pending_by_guard(user_build,
							isl_set_copy(guard));
	user_build = isl_ast_build_set_executed(user_build, executed);
	user_build = isl_ast_build_clear_local_info(user_build);
	if (!user_build)
		node = NULL;
	else
		node = build->create_leaf(user_build, build->create_leaf_user);
	graft = isl_ast_graft_alloc(node, build);
	graft = isl_ast_graft_add_guard(graft, guard, build);
	isl_ast_build_free(build);
	return isl_ast_graft_list_from_ast_graft(graft);
}
