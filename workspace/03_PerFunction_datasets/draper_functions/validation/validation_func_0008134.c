cmd_comment(struct llist_t *arglist)
{
	if(ShowTokens)
	{
		PrintToken(COMMENT, "#", "comment");

		int count = 0;
		char argN[] = "arg 0000";
		struct llist_t *iter = arglist;
		ll_foreach(iter, {
			count++;
			sprintf(argN, "arg %4d",  count);
			PrintToken(iter->value->ttype, iter->value->value, argN);
		});
	}
}
