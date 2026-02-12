static size_t prvWriteBytesToBuffer( StreamBuffer_t * const pxStreamBuffer,
                                     const uint8_t * pucData,
                                     size_t xCount )
{
    size_t xNextHead, xFirstLength;

    configASSERT( xCount > ( size_t ) 0 );

    xNextHead = pxStreamBuffer->xHead;


    xFirstLength = configMIN( pxStreamBuffer->xLength - xNextHead, xCount );


    configASSERT( ( xNextHead + xFirstLength ) <= pxStreamBuffer->xLength );
    ( void ) memcpy( ( void * ) ( &( pxStreamBuffer->pucBuffer[ xNextHead ] ) ), ( const void * ) pucData, xFirstLength );


    if( xCount > xFirstLength )
    {

        configASSERT( ( xCount - xFirstLength ) <= pxStreamBuffer->xLength );
        ( void ) memcpy( ( void * ) pxStreamBuffer->pucBuffer, ( const void * ) &( pucData[ xFirstLength ] ), xCount - xFirstLength );
    }
    else
    {
        mtCOVERAGE_TEST_MARKER();
    }

    xNextHead += xCount;

    if( xNextHead >= pxStreamBuffer->xLength )
    {
        xNextHead -= pxStreamBuffer->xLength;
    }
    else
    {
        mtCOVERAGE_TEST_MARKER();
    }

    pxStreamBuffer->xHead = xNextHead;

    return xCount;
}
