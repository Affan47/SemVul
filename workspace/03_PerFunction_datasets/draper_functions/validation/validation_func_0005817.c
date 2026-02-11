_load_hash_file( const char *filename, int *size )
{
	int flen;
	char *pd = NULL;
	FILE *tf;

	tf = open_file_get_length( filename, "rb", &flen );
	if ( tf == NULL ) {
		goto err_load_file;
	}
	pd = ALC( char, flen );
	if ( pd == NULL ) {
		goto err_load_file;
	}
	if ( fread( pd, flen, 1, tf ) != 1 ) {
		goto err_load_file;
	}
	fclose( tf );
	if ( size != NULL )
		*size = flen;
	return pd;

err_load_file:
	if ( pd != NULL )
		free( pd );
	if ( tf != NULL )
		fclose( tf );
	return NULL;
}
