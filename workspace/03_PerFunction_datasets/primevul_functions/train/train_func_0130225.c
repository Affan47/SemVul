innodb_unknown_command(

	ENGINE_HANDLE*	handle,
	const void*	cookie,
	protocol_binary_request_header *request,
	ADD_RESPONSE	response)
{
	struct innodb_engine* innodb_eng = innodb_handle(handle);
	struct default_engine *def_eng = default_handle(innodb_eng);

	return(def_eng->engine.unknown_command(innodb_eng->default_engine,
					       cookie, request, response));
}
