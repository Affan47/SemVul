innodb_get_info(

	ENGINE_HANDLE*	handle)
{
	return(&innodb_handle(handle)->info.info);
}
