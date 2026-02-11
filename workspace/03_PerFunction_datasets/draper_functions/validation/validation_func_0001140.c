ripemd160_file( const char *path, unsigned char output[20] )
{
    FILE *f;
    size_t n;
    ripemd160_context ctx;
    unsigned char buf[1024];

    if( ( f = fopen( path, "rb" ) ) == NULL )
        return( POLARSSL_ERR_RIPEMD160_FILE_IO_ERROR );

    ripemd160_starts( &ctx );

    while( ( n = fread( buf, 1, sizeof( buf ), f ) ) > 0 )
        ripemd160_update( &ctx, buf, n );

    ripemd160_finish( &ctx, output );

    memset( &ctx, 0, sizeof( ripemd160_context ) );

    if( ferror( f ) != 0 )
    {
        fclose( f );
        return( POLARSSL_ERR_RIPEMD160_FILE_IO_ERROR );
    }

    fclose( f );
    return( 0 );
}
