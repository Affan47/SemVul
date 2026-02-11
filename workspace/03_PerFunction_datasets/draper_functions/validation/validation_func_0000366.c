pull_varnos_walker(Node *node, pull_varnos_context *context)
{
	if (node == NULL)
		return false;
	if (IsA(node, Var))
	{
		Var		   *var = (Var *) node;

		if (var->varlevelsup == context->sublevels_up)
			context->varnos = bms_add_member(context->varnos, var->varno);
		return false;
	}
	if (IsA(node, CurrentOfExpr))
	{
		CurrentOfExpr *cexpr = (CurrentOfExpr *) node;

		if (context->sublevels_up == 0)
			context->varnos = bms_add_member(context->varnos, cexpr->cvarno);
		return false;
	}
	if (IsA(node, PlaceHolderVar))
	{


		PlaceHolderVar *phv = (PlaceHolderVar *) node;
		pull_varnos_context subcontext;

		subcontext.varnos = NULL;
		subcontext.sublevels_up = context->sublevels_up;
		(void) pull_varnos_walker((Node *) phv->phexpr, &subcontext);
		if (phv->phlevelsup == context->sublevels_up)
		{
			subcontext.varnos = bms_int_members(subcontext.varnos,
												phv->phrels);
			if (bms_is_empty(subcontext.varnos))
				context->varnos = bms_add_members(context->varnos,
												  phv->phrels);
		}
		context->varnos = bms_join(context->varnos, subcontext.varnos);
		return false;
	}
	if (IsA(node, Query))
	{

		bool		result;

		context->sublevels_up++;
		result = query_tree_walker((Query *) node, pull_varnos_walker,
								   (void *) context, 0);
		context->sublevels_up--;
		return result;
	}
	return expression_tree_walker(node, pull_varnos_walker,
								  (void *) context);
}
