static rsRetVal qAddDisk(qqueue_t *pThis, void* pUsr)
{
	DEFiRet;
	number_t nWriteCount;

	ASSERT(pThis != NULL);

	CHKiRet(strm.SetWCntr(pThis->tVars.disk.pWrite, &nWriteCount));
	CHKiRet((objSerialize(pUsr))(pUsr, pThis->tVars.disk.pWrite));
	CHKiRet(strm.Flush(pThis->tVars.disk.pWrite));
	CHKiRet(strm.SetWCntr(pThis->tVars.disk.pWrite, NULL));

	pThis->tVars.disk.sizeOnDisk += nWriteCount;


	objDestruct(pUsr);

	DBGOPRINT((obj_t*) pThis, "write wrote %lld octets to disk, queue disk size now %lld octets, EnqOnly:%d\n",
		   nWriteCount, pThis->tVars.disk.sizeOnDisk, pThis->bEnqOnly);

finalize_it:
	RETiRet;
}
