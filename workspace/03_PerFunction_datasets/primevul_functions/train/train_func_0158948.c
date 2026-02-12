static void MsgUnlockLockingCase(msg_t *pThis)
{

	assert(pThis != NULL);
	if(pThis->bDoLock == 1)
		pthread_mutex_unlock(&pThis->mut);
}
