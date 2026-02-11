process_status_update_unknown_total(
     process_status_t *process_status,
     size64_t bytes_read,
     libcerror_error_t **error )
{
	static char *function    = "process_status_update_unknown_total";
	time_t seconds_current   = 0;
	time_t timestamp_current = 0;

	if( process_status == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid process status.",
		 function );

		return( -1 );
	}
	if( ( process_status->output_stream != NULL )
	 && ( process_status->print_status_information != 0 )
	 && ( process_status->status_update_string != NULL ) )
	{
		timestamp_current = time( NULL );

		if( timestamp_current > process_status->last_timestamp )
		{


			if( ( process_status->last_bytes_total == 0 )
			 || ( bytes_read > ( process_status->last_bytes_total + ( 10 * 1024 * 1024 ) ) )
			 || ( ( timestamp_current - process_status->last_timestamp ) > 30 ) )
			{
				process_status->last_timestamp   = timestamp_current;
				process_status->last_bytes_total = bytes_read;

				fprintf(
				 process_status->output_stream,
				 "Status: %" PRIs_LIBCSTRING_SYSTEM "",
				 process_status->status_update_string );

				process_status_bytes_fprint(
				 process_status->output_stream,
				 bytes_read );

				fprintf(
				 process_status->output_stream,
				 "\n" );

				seconds_current = timestamp_current - process_status->start_timestamp;

				fprintf(
				 process_status->output_stream,
				 "       " );

				process_status_timestamp_fprint(
				 process_status->output_stream,
				 seconds_current );

				process_status_bytes_per_second_fprint(
				 process_status->output_stream,
				 bytes_read,
				 seconds_current );

				fprintf(
				 process_status->output_stream,
				 ".\n\n" );
			}
		}
	}
	return( 1 );
}
