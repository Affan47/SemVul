unqlite_kv_cursor_init(unqlite *pDb,unqlite_kv_cursor **ppOut)
{
	int rc;
	if( UNQLITE_DB_MISUSE(pDb) || ppOut == 0 ){
		return UNQLITE_CORRUPT;
	}
#if defined(UNQLITE_ENABLE_THREADS)

	 SyMutexEnter(sUnqlMPGlobal.pMutexMethods, pDb->pMutex);
	 if( sUnqlMPGlobal.nThreadingLevel > UNQLITE_THREAD_LEVEL_SINGLE &&
		 UNQLITE_THRD_DB_RELEASE(pDb) ){
			 return UNQLITE_ABORT;
	 }
#endif

	 rc = unqliteInitCursor(pDb,ppOut);
#if defined(UNQLITE_ENABLE_THREADS)

	 SyMutexLeave(sUnqlMPGlobal.pMutexMethods,pDb->pMutex);
#endif
	 return rc;
}
