static void prvInitialiseNewQueue( const UBaseType_t uxQueueLength,
                                   const UBaseType_t uxItemSize,
                                   uint8_t * pucQueueStorage,
                                   const uint8_t ucQueueType,
                                   Queue_t * pxNewQueue )
{


    ( void ) ucQueueType;

    if( uxItemSize == ( UBaseType_t ) 0 )
    {


        pxNewQueue->pcHead = ( int8_t * ) pxNewQueue;
    }
    else
    {

        pxNewQueue->pcHead = ( int8_t * ) pucQueueStorage;
    }


    pxNewQueue->uxLength = uxQueueLength;
    pxNewQueue->uxItemSize = uxItemSize;
    ( void ) xQueueGenericReset( pxNewQueue, pdTRUE );

    #if ( configUSE_TRACE_FACILITY == 1 )
        {
            pxNewQueue->ucQueueType = ucQueueType;
        }
    #endif

    #if ( configUSE_QUEUE_SETS == 1 )
        {
            pxNewQueue->pxQueueSetContainer = NULL;
        }
    #endif

    traceQUEUE_CREATE( pxNewQueue );
}
