ueStrSeek( char *src, size_t n )
{
	int i = 0;
	char *iter = src;
	for ( i = 0; i < n; i++ ) {
		iter += ueBytesFromChar( iter[0] );
	}
	return iter;
}
