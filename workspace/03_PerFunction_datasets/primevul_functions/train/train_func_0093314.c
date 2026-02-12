int encode_crbits( abitwriter* huffw, abytewriter* storw )
{
    unsigned char* data;
    int len;
    int i;


    len = storw->getpos();
    if ( len == 0 ) return 0;
    data = storw->peekptr_aligned();


    for ( i = 0; i < len; i++ )
        huffw->write( data[ i ], 1 );


    storw->reset();


    return 0;
}
