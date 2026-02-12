void vQueueDelete( QueueHandle_t xQueue )
{
    Queue_t * const pxQueue = xQueue;

    configASSERT( pxQueue );
    traceQUEUE_DELETE( pxQueue );

    #if ( configQUEUE_REGISTRY_SIZE > 0 )
        {
            vQueueUnregisterQueue( pxQueue );
        }
    #endif

    #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 0 ) )
        {


            vPortFree( pxQueue );
        }
    #elif ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )
        {


            if( pxQueue->ucStaticallyAllocated == ( uint8_t ) pdFALSE )
            {
                vPortFree( pxQueue );
            }
            else
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
    #else
        {


            ( void ) pxQueue;
        }
    #endif
}
