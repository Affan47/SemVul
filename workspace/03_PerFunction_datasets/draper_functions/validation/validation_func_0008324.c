parse_debug_unknowns( char **unknowns, int *levelp )
{
	int i, level, rc = 0;

	for ( i = 0; unknowns[ i ] != NULL; i++ ) {
		level = 0;
		if ( str2loglevel( unknowns[ i ], &level )) {
			fprintf( stderr,
				"unrecognized log level \"%s\"\n", unknowns[ i ] );
			rc = 1;
		} else {
			*levelp |= level;
		}
	}
	return rc;
}
