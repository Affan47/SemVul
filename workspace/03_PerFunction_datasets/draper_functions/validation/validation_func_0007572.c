InitEasySymbolInput( const char *prefix )
{
	const char DIRPATH_SEP_FILENAME[] = "%s" PLAT_SEPARATOR "%s";
	FILE *file;
	char filename[ PATH_MAX ];
	char line[ 512 ];
	char *symbol;
	int len = 0, index;

	sprintf( filename, DIRPATH_SEP_FILENAME, prefix, SOFTKBD_TABLE_FILE );
	file = fopen( filename, "r" );

	if ( ! file )
		return 0;

	line[ 0 ] = '\0';
	while ( fgets( line, sizeof( line ) / sizeof( char ), file ) ) {
		if ( '\0' == line[ 0 ] ) {
			break;
		}

		line[ sizeof( line ) / sizeof( char ) - 1] = '\0';
		if ( ' ' != line[ 1 ] ) {
			continue;
		}

		len = strcspn( line, "\r\n\0" );
		line[ len ] = '\0';

		line[ 0 ] = toupper( line[ 0 ] );
		index = FindEasySymbolIndex( line[ 0 ] );
		if ( -1 == index ) {
			continue;
		}

		len = ueStrLen( &line[ 2 ] );
		if ( 0 == len || 10 <= len ) {
			continue;
		}

		symbol = ALC( char, 6 * 10 );
		if ( NULL == symbol ) {
			break;
		}
		ueStrNCpy( symbol, &line[ 2 ], 9, 1 );

		if ( NULL != g_easy_symbol_value[ index] ) {
			free( g_easy_symbol_value[ index ] );
		}
		g_easy_symbol_value[ index ] = symbol;
		g_easy_symbol_num[ index ] = len;
	}
	fclose( file );
	return 1;
}
