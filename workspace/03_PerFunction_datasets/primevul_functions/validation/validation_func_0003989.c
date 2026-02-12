static size_t prvWriteMessageToBuffer( StreamBuffer_t * const pxStreamBuffer,
                                       const void * pvTxData,
                                       size_t xDataLengthBytes,
                                       size_t xSpace,
                                       size_t xRequiredSpace )
{
    BaseType_t xShouldWrite;
    size_t xReturn;

    if( xSpace == ( size_t ) 0 )
    {


        xShouldWrite = pdFALSE;
    }
    else if( ( pxStreamBuffer->ucFlags & sbFLAGS_IS_MESSAGE_BUFFER ) == ( uint8_t ) 0 )
    {


        xShouldWrite = pdTRUE;
        xDataLengthBytes = configMIN( xDataLengthBytes, xSpace );
    }
    else if( xSpace >= xRequiredSpace )
    {


        xShouldWrite = pdTRUE;
        ( void ) prvWriteBytesToBuffer( pxStreamBuffer, ( const uint8_t * ) &( xDataLengthBytes ), sbBYTES_TO_STORE_MESSAGE_LENGTH );
    }
    else
    {

        xShouldWrite = pdFALSE;
    }

    if( xShouldWrite != pdFALSE )
    {

        xReturn = prvWriteBytesToBuffer( pxStreamBuffer, ( const uint8_t * ) pvTxData, xDataLengthBytes );
    }
    else
    {
        xReturn = 0;
    }

    return xReturn;
}
