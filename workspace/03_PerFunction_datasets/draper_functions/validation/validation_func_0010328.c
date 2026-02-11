libsmdev_handle_set_error_flags(
     libsmdev_handle_t *handle,
     uint8_t error_flags,
     libcerror_error_t **error )
{
	libsmdev_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libsmdev_handle_set_error_flags";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libsmdev_internal_handle_t *) handle;

	if( ( error_flags & ~( LIBSMDEV_ERROR_FLAG_ZERO_ON_ERROR ) ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported error flags.",
		 function );

		return( -1 );
	}
	internal_handle->error_flags = error_flags;

	return( 1 );
}
