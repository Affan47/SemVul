gettoken( char *line, char *dst )
{
    char *ptr = dst;
    char ch;

    do{
	ch = *line++;
	if( ch == '\0' ) return( NULL );

    } while( ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' );
    while( 1 ){
	*ptr++ = ch;
	ch = *line++;
	if( ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' ){
	    *ptr = '\0';
	    return( line );
	}
	if( ch == '\0' ){
	    *ptr = '\0';
	    return( line - 1 );
	}
    }
}
