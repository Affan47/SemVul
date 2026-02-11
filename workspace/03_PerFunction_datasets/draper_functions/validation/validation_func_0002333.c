_THKERNEL( LPVOID lpvData
		  )
{
	CThread *pThread = (CThread *)lpvData;
	ThreadType_t lastType;


    pThread->m_mutex.Lock();
		pThread->m_state = ThreadStateWaiting;
		pThread->m_bRunning = TRUE;
#ifndef WINDOWS
		pThread->m_dwId = CThread::ThreadId();
#endif
	pThread->m_mutex.Unlock();

	while( TRUE )
	{
		lastType = pThread->m_type;

		if( lastType == ThreadTypeHomogeneous ||
			lastType == ThreadTypeSpecialized ||
			lastType == ThreadTypeNotDefined )
		{
			if( ! pThread->m_event.Wait()  )
					break;
			pThread->m_event.Reset();
		}

		if( ! pThread->KernelProcess() )
				break;


		if( pThread->m_type == ThreadTypeIntervalDriven )
			Sleep(pThread->m_dwIdle);

	}


	pThread->m_mutex.Lock();
		pThread->m_state = ThreadStateDown;
		pThread->m_bRunning = FALSE;
	pThread->m_mutex.Unlock();


#ifdef WINDOWS
	return 0;
#else
	return (LPVOID)0;
#endif
}
