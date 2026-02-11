buf_pointer_is_block_field(

	const void*	ptr)
{
	ulint	i;

	for (i = 0; i < srv_buf_pool_instances; i++) {
		ibool	found;

		found = buf_pointer_is_block_field_instance(
			buf_pool_from_array(i), ptr);
		if (found) {
			return(TRUE);
		}
	}

	return(FALSE);
}
