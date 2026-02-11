int_unregister_cb_doall_arg(ENGINE_PILE *pile, ENGINE *e)
	{
	int n;

	while((n = sk_ENGINE_find(pile->sk, e)) >= 0)
		{
		(void)sk_ENGINE_delete(pile->sk, n);
		pile->uptodate = 0;
		}
	if(pile->funct == e)
		{
		engine_unlocked_finish(e, 0);
		pile->funct = NULL;
		}
	}
