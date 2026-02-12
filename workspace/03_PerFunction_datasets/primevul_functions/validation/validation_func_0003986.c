void vStreamBufferDelete( StreamBufferHandle_t xStreamBuffer )
{
    StreamBuffer_t * pxStreamBuffer = xStreamBuffer;

    configASSERT( pxStreamBuffer );

    traceSTREAM_BUFFER_DELETE( xStreamBuffer );

    if( ( pxStreamBuffer->ucFlags & sbFLAGS_IS_STATICALLY_ALLOCATED ) == ( uint8_t ) pdFALSE )
    {
        #if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
            {


                vPortFree( ( void * ) pxStreamBuffer );
            }
        #else
            {


                configASSERT( xStreamBuffer == ( StreamBufferHandle_t ) ~0 );
            }
        #endif
    }
    else
    {


        ( void ) memset( pxStreamBuffer, 0x00, sizeof( StreamBuffer_t ) );
    }
}
