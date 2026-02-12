static inline void prepareProgramName(msg_t *pM, sbool bLockMutex)
{
	if(pM->pCSProgName == NULL) {
		if(bLockMutex == LOCK_MUTEX)
			MsgLock(pM);


		if(pM->pCSProgName == NULL)
			aquireProgramName(pM);

		if(bLockMutex == LOCK_MUTEX)
			MsgUnlock(pM);
	}
}
