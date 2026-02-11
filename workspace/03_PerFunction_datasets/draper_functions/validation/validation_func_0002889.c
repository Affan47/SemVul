my_input( unsigned char *buf, int max_size )
{
    if ( ! infile.eof() )
        infile.getline( listing_line, sizeof( listing_line ) );

    if ( infile.eof() )
    {
        listing_line[ 0 ] = '\0';
        *buf = '\0';
        return 0;
    }
    else
    {
        char *s;


        strcat( listing_line, "\n" );
        if ( listing )
            detab( listing_line );
        line++;
        for( s = listing_line; *s; s++ )
            *buf++ = toupper( *s );
        return( s - listing_line );
    }
}
