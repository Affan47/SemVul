SclBufferIsPartialReply( void * dataptr, int datalen )
{
    int i = 0, value = 0;
    unsigned char * const data = dataptr;
    unsigned int d;

    if( i >= datalen )
    {
        return 0;
    }
    if( data[i++] != 27 )
    {
        return 0;
    }
    if( i >= datalen )
    {
        return 0;
    }
    if( data[i++] != '*' )
    {
        return 0;
    }
    if( i >= datalen )
    {
        return 0;
    }
    if( data[i++] != 's' )
    {
        return 0;
    }
    while( 42 )
    {
        if( i >= datalen )
        {
            return 0;
        }
        d = data[i] - '0';
        if( d > 9 )
        {
            break;
        }
        i++;
    }
    d = data[i++];
    if( d<'a' || d>'z' )
    {
        return 0;
    }
    while( 42 )
    {
        if( i >= datalen )
        {
            return 0;
        }
        d = data[i] - '0';
        if( d > 9 )
        {
            break;
        }
        i++;
        value = ( value * 10 ) + d;
    }
    if( i >= datalen )
    {
        return 0;
    }
    if( data[i++] != 'W' )
    {
        return 0;
    }
    value = i + value - datalen;
    if( value < 0 )
    {
        value = 0;
    }
    return value;
}
