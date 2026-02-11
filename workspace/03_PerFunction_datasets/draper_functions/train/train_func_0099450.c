x509parse_keyfile( rsa_context *rsa, const char *path, const char *pwd )
{
    int ret;
    size_t n;
    unsigned char *buf;

    if ( (ret = load_file( path, &buf, &n ) ) != 0 )
        return( ret );

    if( pwd == NULL )
        ret = x509parse_key( rsa, buf, n, NULL, 0 );
    else
        ret = x509parse_key( rsa, buf, n,
                (unsigned char *) pwd, strlen( pwd ) );

    memset( buf, 0, n + 1 );
    free( buf );

    return( ret );
}
