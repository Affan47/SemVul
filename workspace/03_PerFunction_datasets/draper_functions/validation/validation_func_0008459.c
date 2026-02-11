do_fsize( char* vfilename, char* filename, FILE* fp, char* directive, char* tag, char* val )
    {
    char filename2[1000];


    if ( get_filename(
	     vfilename, filename, directive, tag, val, filename2,
	     sizeof(filename2) ) < 0 )
	return;
    if ( stat( filename2, &sb ) < 0 )
	{
	not_found2( directive, tag, filename2 );
	return;
	}
    show_size( sb.st_size );
    }
