static void prvInitialiseMutex( Queue_t * pxNewQueue )
    {
        if( pxNewQueue != NULL )
        {


            pxNewQueue->u.xSemaphore.xMutexHolder = NULL;
            pxNewQueue->uxQueueType = queueQUEUE_IS_MUTEX;


            pxNewQueue->u.xSemaphore.uxRecursiveCallCount = 0;

            traceCREATE_MUTEX( pxNewQueue );


            ( void ) xQueueGenericSend( pxNewQueue, NULL, ( TickType_t ) 0U, queueSEND_TO_BACK );
        }
        else
        {
            traceCREATE_MUTEX_FAILED();
        }
    }
