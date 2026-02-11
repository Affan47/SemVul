libcfile_stream_open(
     libcfile_stream_t *stream,
     const char *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libcfile_internal_stream_t *internal_stream = NULL;
	const char *stream_io_mode                  = NULL;
	static char *function                       = "libcfile_stream_open";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libcfile_internal_stream_t *) stream;

	if( ( ( access_flags & LIBCFILE_ACCESS_FLAG_READ ) != 0 )
	 && ( ( access_flags & LIBCFILE_ACCESS_FLAG_WRITE ) != 0 ) )
	{
		if( ( access_flags & LIBCFILE_ACCESS_FLAG_TRUNCATE ) != 0 )
		{
			stream_io_mode = "wb+";
		}
		else
		{
			stream_io_mode = "ab+";
		}
	}
	else if( ( access_flags & LIBCFILE_ACCESS_FLAG_READ ) != 0 )
	{
		stream_io_mode = "rb";
	}
	else if( ( access_flags & LIBCFILE_ACCESS_FLAG_WRITE ) != 0 )
	{
		if( ( access_flags & LIBCFILE_ACCESS_FLAG_TRUNCATE ) != 0 )
		{
			stream_io_mode = "wb";
		}
		else
		{
			stream_io_mode = "ab";
		}
	}
	else
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags: 0x%02x.",
		 function,
		 access_flags );

		return( -1 );
	}
#if defined( HAVE_GLIB_H )
	internal_stream->stream = g_fopen(
	                           filename,
	                           stream_io_mode );
#else
	internal_stream->stream = fopen(
	                           filename,
	                           stream_io_mode );
#endif
	if( internal_stream->stream == NULL )
	{
		switch( errno )
		{
			case EACCES:
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_ACCESS_DENIED,
				 "%s: access denied to file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;

			case ENOENT:
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_INVALID_RESOURCE,
				 "%s: no such file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;

			default:
				libcerror_system_set_error(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_OPEN_FAILED,
				 errno,
				 "%s: unable to open file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;
		}
		return( -1 );
	}
	return( 1 );
}
