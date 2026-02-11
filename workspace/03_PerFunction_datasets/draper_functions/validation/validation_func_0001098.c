in_last_colon( bool say_in )
{
    if ( print_msg )
    {
	if ( incolon || ( ! say_in ) )
	{
	    fprintf( message_dest, "%s definition of  %s ", say_in ? " in" : "",
		strupr( last_colon_defname) );
	    print_where_started( TRUE, FALSE,
		last_colon_filename, last_colon_lineno, FALSE);
	}else{
	    fprintf(message_dest, "\n");
	}
    }
}
