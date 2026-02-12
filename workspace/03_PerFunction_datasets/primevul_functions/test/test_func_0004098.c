BaseType_t xQueueRemoveFromSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                    QueueSetHandle_t xQueueSet )
    {
        BaseType_t xReturn;
        Queue_t * const pxQueueOrSemaphore = ( Queue_t * ) xQueueOrSemaphore;

        if( pxQueueOrSemaphore->pxQueueSetContainer != xQueueSet )
        {

            xReturn = pdFAIL;
        }
        else if( pxQueueOrSemaphore->uxMessagesWaiting != ( UBaseType_t ) 0 )
        {


            xReturn = pdFAIL;
        }
        else
        {
            taskENTER_CRITICAL();
            {

                pxQueueOrSemaphore->pxQueueSetContainer = NULL;
            }
            taskEXIT_CRITICAL();
            xReturn = pdPASS;
        }

        return xReturn;
    }
