display_cond_expressions()
{
	cond_node_t *cur;

	for (cur = policydbp->cond_list; cur != NULL; cur = cur->next) {
		printf("expression: ");
		display_expr(cur->expr);
		printf("current state: %d\n", cur->cur_state);
	}
	return 0;
}
