innodb_get_stats(

	ENGINE_HANDLE*		handle,
	const void*		cookie,
	const char*		stat_key,
	int			nkey,
	ADD_STAT		add_stat)
{
	struct innodb_engine* innodb_eng = innodb_handle(handle);
	struct default_engine *def_eng = default_handle(innodb_eng);
	return(def_eng->engine.get_stats(innodb_eng->default_engine, cookie,
					 stat_key, nkey, add_stat));
}
