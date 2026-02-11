add_actions(struct action* a, struct action** head)
{
	int ret;

	LM_DBG("fixing actions...\n");
	if ((ret=fix_actions(a))!=0) goto error;
	push(a,head);
	return 0;

error:
	return ret;
}
