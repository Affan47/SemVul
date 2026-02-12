static void MsgLockLockingCase(msg_t *pThis)
{

	assert(pThis != NULL);
	if(pThis->bDoLock == 1)
		pthread_mutex_lock(&pThis->mut);
}
