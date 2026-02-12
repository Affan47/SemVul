static void create_irp_thread(SERIAL_DEVICE* serial, IRP* irp)
{
	IRP_THREAD_DATA* data = NULL;
	HANDLE irpThread;
	HANDLE previousIrpThread;
	uintptr_t key;


	EnterCriticalSection(&serial->TerminatingIrpThreadsLock);

	while (serial->IrpThreadToBeTerminatedCount > 0)
	{


		HANDLE irpThread;
		ULONG_PTR* ids;
		int i, nbIds;
		nbIds = ListDictionary_GetKeys(serial->IrpThreads, &ids);

		for (i = 0; i < nbIds; i++)
		{

			DWORD waitResult;
			ULONG_PTR id = ids[i];
			irpThread = ListDictionary_GetItemValue(serial->IrpThreads, (void*)id);


			waitResult = WaitForSingleObject(irpThread, 0);

			if (waitResult == WAIT_OBJECT_0)
			{


				CloseHandle(irpThread);
				ListDictionary_Remove(serial->IrpThreads, (void*)id);
				serial->IrpThreadToBeTerminatedCount--;
			}
			else if (waitResult != WAIT_TIMEOUT)
			{

				WLog_Print(serial->log, WLOG_WARN,
				           "WaitForSingleObject, got an unexpected result=0x%" PRIX32 "\n",
				           waitResult);
				assert(FALSE);
			}


		}

		if (serial->IrpThreadToBeTerminatedCount > 0)
		{
			WLog_Print(serial->log, WLOG_DEBUG, "%" PRIu32 " IRP thread(s) not yet terminated",
			           serial->IrpThreadToBeTerminatedCount);
			Sleep(1);
		}

		free(ids);
	}

	LeaveCriticalSection(&serial->TerminatingIrpThreadsLock);


	key = irp->CompletionId;
	previousIrpThread = ListDictionary_GetItemValue(serial->IrpThreads, (void*)key);

	if (previousIrpThread)
	{

		WLog_Print(serial->log, WLOG_DEBUG,
		           "IRP recall: IRP with the CompletionId=%" PRIu32 " not yet completed!",
		           irp->CompletionId);
		assert(FALSE);


		irp->Discard(irp);
		return;
	}

	if (ListDictionary_Count(serial->IrpThreads) >= MAX_IRP_THREADS)
	{
		WLog_Print(serial->log, WLOG_WARN,
		           "Number of IRP threads threshold reached: %d, keep on anyway",
		           ListDictionary_Count(serial->IrpThreads));
		assert(FALSE);


	}


	data = (IRP_THREAD_DATA*)calloc(1, sizeof(IRP_THREAD_DATA));

	if (data == NULL)
	{
		WLog_Print(serial->log, WLOG_WARN, "Could not allocate a new IRP_THREAD_DATA.");
		goto error_handle;
	}

	data->serial = serial;
	data->irp = irp;

	irpThread = CreateThread(NULL, 0, irp_thread_func, (void*)data, 0, NULL);

	if (irpThread == INVALID_HANDLE_VALUE)
	{
		WLog_Print(serial->log, WLOG_WARN, "Could not allocate a new IRP thread.");
		goto error_handle;
	}

	key = irp->CompletionId;

	if (!ListDictionary_Add(serial->IrpThreads, (void*)key, irpThread))
	{
		WLog_ERR(TAG, "ListDictionary_Add failed!");
		goto error_handle;
	}

	return;
error_handle:
	irp->IoStatus = STATUS_NO_MEMORY;
	irp->Complete(irp);
	free(data);
}
