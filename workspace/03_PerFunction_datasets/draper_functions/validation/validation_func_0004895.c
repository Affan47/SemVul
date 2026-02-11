http_digest_param ( char *params, const char *name ) {
	char *key;
	char *value;
	char *terminator;


	key = strstr ( params, name );
	if ( ! key )
		return NULL;


	value = ( key + strlen ( name ) );
	terminator = strchr ( value, '"' );
	if ( ! terminator )
		return NULL;
	return strndup ( value, ( terminator - value ) );
}
