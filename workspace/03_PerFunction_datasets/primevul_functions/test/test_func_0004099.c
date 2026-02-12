const char * pcQueueGetName( QueueHandle_t xQueue )
    {
        UBaseType_t ux;
        const char * pcReturn = NULL;


        for( ux = ( UBaseType_t ) 0U; ux < ( UBaseType_t ) configQUEUE_REGISTRY_SIZE; ux++ )
        {
            if( xQueueRegistry[ ux ].xHandle == xQueue )
            {
                pcReturn = xQueueRegistry[ ux ].pcQueueName;
                break;
            }
            else
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }

        return pcReturn;
    }
