check_key_name_for_map_switch(

	ENGINE_HANDLE*		handle,
	const void*		cookie,
	const void*		key,
	size_t*			nkey)
{
	ENGINE_ERROR_CODE	err_ret = ENGINE_SUCCESS;

	if ((*nkey) > 3 && ((char*)key)[0] == '@'
	    && ((char*)key)[1] == '@') {
		err_ret = innodb_switch_mapping(handle, cookie, key, nkey, true);
	}

	return(err_ret);
}
