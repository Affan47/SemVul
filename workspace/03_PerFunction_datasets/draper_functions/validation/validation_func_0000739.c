OffsetVarNodes_walker(Node *node, OffsetVarNodes_context *context)
{
	if (node == NULL)
		return false;
	if (IsA(node, Var))
	{
		Var		   *var = (Var *) node;

		if (var->varlevelsup == context->sublevels_up)
		{
			var->varno += context->offset;
			var->varnoold += context->offset;
		}
		return false;
	}
	if (IsA(node, CurrentOfExpr))
	{
		CurrentOfExpr *cexpr = (CurrentOfExpr *) node;

		if (context->sublevels_up == 0)
			cexpr->cvarno += context->offset;
		return false;
	}
	if (IsA(node, RangeTblRef))
	{
		RangeTblRef *rtr = (RangeTblRef *) node;

		if (context->sublevels_up == 0)
			rtr->rtindex += context->offset;

		return false;
	}
	if (IsA(node, JoinExpr))
	{
		JoinExpr   *j = (JoinExpr *) node;

		if (context->sublevels_up == 0)
			j->rtindex += context->offset;

	}
	if (IsA(node, InClauseInfo))
	{
		InClauseInfo *ininfo = (InClauseInfo *) node;

		if (context->sublevels_up == 0)
		{
			ininfo->lefthand = offset_relid_set(ininfo->lefthand,
												context->offset);
			ininfo->righthand = offset_relid_set(ininfo->righthand,
												 context->offset);
		}

	}
	if (IsA(node, AppendRelInfo))
	{
		AppendRelInfo *appinfo = (AppendRelInfo *) node;

		if (context->sublevels_up == 0)
		{
			appinfo->parent_relid += context->offset;
			appinfo->child_relid += context->offset;
		}

	}
	if (IsA(node, Query))
	{

		bool		result;

		context->sublevels_up++;
		result = query_tree_walker((Query *) node, OffsetVarNodes_walker,
								   (void *) context, 0);
		context->sublevels_up--;
		return result;
	}
	return expression_tree_walker(node, OffsetVarNodes_walker,
								  (void *) context);
}
