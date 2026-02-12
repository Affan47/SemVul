void vQueueAddToRegistry( QueueHandle_t xQueue,
                              const char * pcQueueName )
    {
        UBaseType_t ux;


        for( ux = ( UBaseType_t ) 0U; ux < ( UBaseType_t ) configQUEUE_REGISTRY_SIZE; ux++ )
        {
            if( xQueueRegistry[ ux ].pcQueueName == NULL )
            {

                xQueueRegistry[ ux ].pcQueueName = pcQueueName;
                xQueueRegistry[ ux ].xHandle = xQueue;

                traceQUEUE_REGISTRY_ADD( xQueue, pcQueueName );
                break;
            }
            else
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
    }
