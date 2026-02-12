innodb_bind(

	ENGINE_HANDLE*		handle,
	const void*		cookie,
	const void*		name,
	size_t			name_len)
{
	ENGINE_ERROR_CODE	err_ret = ENGINE_SUCCESS;

	err_ret = innodb_switch_mapping(handle, cookie, name, &name_len, false);

	return(err_ret);
}
