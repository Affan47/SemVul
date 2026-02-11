plat_mmap_unmap( plat_mmap *handle )
{

	if ( ! handle )
		return;

	if ( handle->address ) {
		munmap( handle->address, handle->sizet );
		handle->address = NULL;
	}
}
