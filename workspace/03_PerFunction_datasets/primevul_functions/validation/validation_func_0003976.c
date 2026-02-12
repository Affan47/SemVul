static size_t prvReadMessageFromBuffer( StreamBuffer_t * pxStreamBuffer,
                                        void * pvRxData,
                                        size_t xBufferLengthBytes,
                                        size_t xBytesAvailable,
                                        size_t xBytesToStoreMessageLength )
{
    size_t xOriginalTail, xReceivedLength, xNextMessageLength;
    configMESSAGE_BUFFER_LENGTH_TYPE xTempNextMessageLength;

    if( xBytesToStoreMessageLength != ( size_t ) 0 )
    {


        xOriginalTail = pxStreamBuffer->xTail;
        ( void ) prvReadBytesFromBuffer( pxStreamBuffer, ( uint8_t * ) &xTempNextMessageLength, xBytesToStoreMessageLength, xBytesAvailable );
        xNextMessageLength = ( size_t ) xTempNextMessageLength;


        xBytesAvailable -= xBytesToStoreMessageLength;


        if( xNextMessageLength > xBufferLengthBytes )
        {


            pxStreamBuffer->xTail = xOriginalTail;
            xNextMessageLength = 0;
        }
        else
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    else
    {


        xNextMessageLength = xBufferLengthBytes;
    }


    xReceivedLength = prvReadBytesFromBuffer( pxStreamBuffer, ( uint8_t * ) pvRxData, xNextMessageLength, xBytesAvailable );

    return xReceivedLength;
}
