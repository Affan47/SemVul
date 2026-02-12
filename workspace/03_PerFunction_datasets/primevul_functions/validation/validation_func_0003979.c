static size_t prvReadBytesFromBuffer( StreamBuffer_t * pxStreamBuffer,
                                      uint8_t * pucData,
                                      size_t xMaxCount,
                                      size_t xBytesAvailable )
{
    size_t xCount, xFirstLength, xNextTail;


    xCount = configMIN( xBytesAvailable, xMaxCount );

    if( xCount > ( size_t ) 0 )
    {
        xNextTail = pxStreamBuffer->xTail;


        xFirstLength = configMIN( pxStreamBuffer->xLength - xNextTail, xCount );


        configASSERT( xFirstLength <= xMaxCount );
        configASSERT( ( xNextTail + xFirstLength ) <= pxStreamBuffer->xLength );
        ( void ) memcpy( ( void * ) pucData, ( const void * ) &( pxStreamBuffer->pucBuffer[ xNextTail ] ), xFirstLength );


        if( xCount > xFirstLength )
        {

            configASSERT( xCount <= xMaxCount );
            ( void ) memcpy( ( void * ) &( pucData[ xFirstLength ] ), ( void * ) ( pxStreamBuffer->pucBuffer ), xCount - xFirstLength );
        }
        else
        {
            mtCOVERAGE_TEST_MARKER();
        }


        xNextTail += xCount;

        if( xNextTail >= pxStreamBuffer->xLength )
        {
            xNextTail -= pxStreamBuffer->xLength;
        }

        pxStreamBuffer->xTail = xNextTail;
    }
    else
    {
        mtCOVERAGE_TEST_MARKER();
    }

    return xCount;
}
