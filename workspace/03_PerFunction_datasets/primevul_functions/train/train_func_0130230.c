innodb_reset_stats(

	ENGINE_HANDLE*		handle,
	const void*		cookie)
{
	struct innodb_engine* innodb_eng = innodb_handle(handle);
	struct default_engine *def_eng = default_handle(innodb_eng);
	def_eng->engine.reset_stats(innodb_eng->default_engine, cookie);
}
