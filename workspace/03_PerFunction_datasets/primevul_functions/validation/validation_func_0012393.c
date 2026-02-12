static rsRetVal qDelDisk(qqueue_t *pThis)
{
	obj_t *pDummyObj;
	DEFiRet;

	int64 offsIn;
	int64 offsOut;

	CHKiRet(strm.GetCurrOffset(pThis->tVars.disk.pReadDel, &offsIn));
	CHKiRet(obj.Deserialize(&pDummyObj, (uchar*) "msg", pThis->tVars.disk.pReadDel, NULL, NULL));
	objDestruct(pDummyObj);
	CHKiRet(strm.GetCurrOffset(pThis->tVars.disk.pReadDel, &offsOut));


	if(offsIn < offsOut) {
		pThis->tVars.disk.bytesRead += offsOut - offsIn;
	} else {
		pThis->tVars.disk.sizeOnDisk -= pThis->tVars.disk.bytesRead;
		pThis->tVars.disk.bytesRead = offsOut;
		DBGOPRINT((obj_t*) pThis, "a file has been deleted, now %lld octets disk space used\n", pThis->tVars.disk.sizeOnDisk);

		pthread_cond_signal(&pThis->notFull);
	}

finalize_it:
	RETiRet;
}
