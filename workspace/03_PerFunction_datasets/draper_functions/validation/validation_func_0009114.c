uxTaskGetSystemState( TaskStatus_t * const pxTaskStatusArray, const UBaseType_t uxArraySize, uint32_t * const pulTotalRunTime )
	{
	UBaseType_t uxTask = 0, uxQueue = configMAX_PRIORITIES;

		vTaskSuspendAll();
		{

			if( uxArraySize >= uxCurrentNumberOfTasks )
			{


				do
				{
					uxQueue--;
					uxTask += prvListTaskWithinSingleList( &( pxTaskStatusArray[ uxTask ] ), &( pxReadyTasksLists[ uxQueue ] ), eReady );

				} while( uxQueue > ( UBaseType_t ) tskIDLE_PRIORITY );


				uxTask += prvListTaskWithinSingleList( &( pxTaskStatusArray[ uxTask ] ), ( List_t * ) pxDelayedTaskList, eBlocked );
				uxTask += prvListTaskWithinSingleList( &( pxTaskStatusArray[ uxTask ] ), ( List_t * ) pxOverflowDelayedTaskList, eBlocked );

				#if( INCLUDE_vTaskDelete == 1 )
				{


					uxTask += prvListTaskWithinSingleList( &( pxTaskStatusArray[ uxTask ] ), &xTasksWaitingTermination, eDeleted );
				}
				#endif

				#if ( INCLUDE_vTaskSuspend == 1 )
				{


					uxTask += prvListTaskWithinSingleList( &( pxTaskStatusArray[ uxTask ] ), &xSuspendedTaskList, eSuspended );
				}
				#endif

				#if ( configGENERATE_RUN_TIME_STATS == 1)
				{
					if( pulTotalRunTime != NULL )
					{
						#ifdef portALT_GET_RUN_TIME_COUNTER_VALUE
							portALT_GET_RUN_TIME_COUNTER_VALUE( ( *pulTotalRunTime ) );
						#else
							*pulTotalRunTime = portGET_RUN_TIME_COUNTER_VALUE();
						#endif
					}
				}
				#else
				{
					if( pulTotalRunTime != NULL )
					{
						*pulTotalRunTime = 0;
					}
				}
				#endif
			}
			else
			{
				mtCOVERAGE_TEST_MARKER();
			}
		}
		( void ) xTaskResumeAll();

		return uxTask;
	}
