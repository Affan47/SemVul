libuna_utf8_string_size_from_utf7_stream(
     const uint8_t *utf7_stream,
     size_t utf7_stream_size,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	static char *function                        = "libuna_utf8_string_size_from_utf7_stream";
	size_t utf7_stream_index                     = 0;
	libuna_unicode_character_t unicode_character = 0;
	uint32_t utf7_stream_base64_data             = 0;

	if( utf7_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-7 stream.",
		 function );

		return( -1 );
	}
	if( utf7_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-7 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf7_stream_size < 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: missing UTF-7 stream bytes.",
		 function );

		return( -1 );
	}
	if( utf8_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string size.",
		 function );

		return( -1 );
	}
	*utf8_string_size = 0;


	if( utf7_stream[ utf7_stream_size - 1 ] != 0 )
	{
		*utf8_string_size += 1;
	}
	while( utf7_stream_index < utf7_stream_size )
	{


		if( libuna_unicode_character_copy_from_utf7_stream(
		     &unicode_character,
		     utf7_stream,
		     utf7_stream_size,
		     &utf7_stream_index,
		     &utf7_stream_base64_data,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-7 stream.",
			 function );

			return( -1 );
		}


		if( libuna_unicode_character_size_to_utf8(
		     unicode_character,
		     utf8_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to unable to determine size of Unicode character in UTF-8.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}
