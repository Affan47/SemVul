query_transactions(struct dundi_request *dr)
{
	struct dundi_transaction *trans;

	AST_LIST_LOCK(&peers);
	AST_LIST_TRAVERSE(&dr->trans, trans, parentlist) {
		dundi_query(trans);
	}
	AST_LIST_UNLOCK(&peers);

	return 0;
}
