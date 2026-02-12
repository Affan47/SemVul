QueueHandle_t xQueueGenericCreateStatic( const UBaseType_t uxQueueLength,
                                             const UBaseType_t uxItemSize,
                                             uint8_t * pucQueueStorage,
                                             StaticQueue_t * pxStaticQueue,
                                             const uint8_t ucQueueType )
    {
        Queue_t * pxNewQueue;

        configASSERT( uxQueueLength > ( UBaseType_t ) 0 );


        configASSERT( pxStaticQueue != NULL );


        configASSERT( !( ( pucQueueStorage != NULL ) && ( uxItemSize == 0 ) ) );
        configASSERT( !( ( pucQueueStorage == NULL ) && ( uxItemSize != 0 ) ) );

        #if ( configASSERT_DEFINED == 1 )
            {


                volatile size_t xSize = sizeof( StaticQueue_t );
                configASSERT( xSize == sizeof( Queue_t ) );
                ( void ) xSize;
            }
        #endif


        pxNewQueue = ( Queue_t * ) pxStaticQueue;

        if( pxNewQueue != NULL )
        {
            #if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
                {


                    pxNewQueue->ucStaticallyAllocated = pdTRUE;
                }
            #endif

            prvInitialiseNewQueue( uxQueueLength, uxItemSize, pucQueueStorage, ucQueueType, pxNewQueue );
        }
        else
        {
            traceQUEUE_CREATE_FAILED( ucQueueType );
            mtCOVERAGE_TEST_MARKER();
        }

        return pxNewQueue;
    }
