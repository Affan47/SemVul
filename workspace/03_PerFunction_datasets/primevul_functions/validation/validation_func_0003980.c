BaseType_t xStreamBufferReset( StreamBufferHandle_t xStreamBuffer )
{
    StreamBuffer_t * const pxStreamBuffer = xStreamBuffer;
    BaseType_t xReturn = pdFAIL;

    #if ( configUSE_TRACE_FACILITY == 1 )
        UBaseType_t uxStreamBufferNumber;
    #endif

    configASSERT( pxStreamBuffer );

    #if ( configUSE_TRACE_FACILITY == 1 )
        {


            uxStreamBufferNumber = pxStreamBuffer->uxStreamBufferNumber;
        }
    #endif


    taskENTER_CRITICAL();
    {
        if( pxStreamBuffer->xTaskWaitingToReceive == NULL )
        {
            if( pxStreamBuffer->xTaskWaitingToSend == NULL )
            {
                prvInitialiseNewStreamBuffer( pxStreamBuffer,
                                              pxStreamBuffer->pucBuffer,
                                              pxStreamBuffer->xLength,
                                              pxStreamBuffer->xTriggerLevelBytes,
                                              pxStreamBuffer->ucFlags );
                xReturn = pdPASS;

                #if ( configUSE_TRACE_FACILITY == 1 )
                    {
                        pxStreamBuffer->uxStreamBufferNumber = uxStreamBufferNumber;
                    }
                #endif

                traceSTREAM_BUFFER_RESET( xStreamBuffer );
            }
        }
    }
    taskEXIT_CRITICAL();

    return xReturn;
}
