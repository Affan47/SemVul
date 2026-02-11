MemHashCursorSeek(unqlite_kv_cursor *pCursor,const void *pKey,int nByte,int iPos)
{
	mem_hash_kv_engine *pEngine = (mem_hash_kv_engine *)pCursor->pStore;
	mem_hash_cursor *pMem = (mem_hash_cursor *)pCursor;

	pMem->pCur = MemHashGetEntry(pEngine,pKey,nByte);
	if( pMem->pCur == 0 ){
		if( iPos != UNQLITE_CURSOR_MATCH_EXACT ){

		}

		return UNQLITE_NOTFOUND;
	}
	return UNQLITE_OK;
}
