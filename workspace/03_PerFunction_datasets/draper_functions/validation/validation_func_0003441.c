asn1_write_mpi( unsigned char **p, unsigned char *start, mpi *X )
{
    int ret;
    size_t len = 0;


    len = mpi_size( X );

    if( *p - start < (int) len )
        return( POLARSSL_ERR_ASN1_BUF_TOO_SMALL );

    (*p) -= len;
    mpi_write_binary( X, *p, len );


    if ( X->s ==1 && **p & 0x80 )
    {
        if( *p - start < 1 )
            return( POLARSSL_ERR_ASN1_BUF_TOO_SMALL );

        *--(*p) = 0x00;
        len += 1;
    }

    ASN1_CHK_ADD( len, asn1_write_len( p, start, len ) );
    ASN1_CHK_ADD( len, asn1_write_tag( p, start, ASN1_INTEGER ) );

    return( len );
}
