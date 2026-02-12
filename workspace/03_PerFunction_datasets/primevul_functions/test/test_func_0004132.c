TaskHandle_t xQueueGetMutexHolder( QueueHandle_t xSemaphore )
    {
        TaskHandle_t pxReturn;
        Queue_t * const pxSemaphore = ( Queue_t * ) xSemaphore;


        taskENTER_CRITICAL();
        {
            if( pxSemaphore->uxQueueType == queueQUEUE_IS_MUTEX )
            {
                pxReturn = pxSemaphore->u.xSemaphore.xMutexHolder;
            }
            else
            {
                pxReturn = NULL;
            }
        }
        taskEXIT_CRITICAL();

        return pxReturn;
    }
