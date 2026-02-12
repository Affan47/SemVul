qqueueTryLoadPersistedInfo(qqueue_t *pThis)
{
	DEFiRet;
	strm_t *psQIF = NULL;
	uchar pszQIFNam[MAXFNAME];
	size_t lenQIFNam;
	struct stat stat_buf;

	ISOBJ_TYPE_assert(pThis, qqueue);


	lenQIFNam = snprintf((char*)pszQIFNam, sizeof(pszQIFNam) / sizeof(uchar), "%s/%s.qi",
			     (char*) glbl.GetWorkDir(), (char*)pThis->pszFilePrefix);


	if(stat((char*) pszQIFNam, &stat_buf) == -1) {
		if(errno == ENOENT) {
			DBGOPRINT((obj_t*) pThis, "clean startup, no .qi file found\n");
			ABORT_FINALIZE(RS_RET_FILE_NOT_FOUND);
		} else {
			DBGOPRINT((obj_t*) pThis, "error %d trying to access .qi file\n", errno);
			ABORT_FINALIZE(RS_RET_IO_ERROR);
		}
	}


	CHKiRet(strm.Construct(&psQIF));
	CHKiRet(strm.SettOperationsMode(psQIF, STREAMMODE_READ));
	CHKiRet(strm.SetsType(psQIF, STREAMTYPE_FILE_SINGLE));
	CHKiRet(strm.SetFName(psQIF, pszQIFNam, lenQIFNam));
	CHKiRet(strm.ConstructFinalize(psQIF));


	CHKiRet(obj.DeserializePropBag((obj_t*) pThis, psQIF));


	CHKiRet(obj.Deserialize(&pThis->tVars.disk.pWrite, (uchar*) "strm", psQIF,
			       (rsRetVal(*)(obj_t*,void*))qqueueLoadPersStrmInfoFixup, pThis));
	CHKiRet(obj.Deserialize(&pThis->tVars.disk.pReadDel, (uchar*) "strm", psQIF,
			       (rsRetVal(*)(obj_t*,void*))qqueueLoadPersStrmInfoFixup, pThis));


	CHKiRet(strm.Dup(pThis->tVars.disk.pReadDel, &pThis->tVars.disk.pReadDeq));
	CHKiRet(strm.SetbDeleteOnClose(pThis->tVars.disk.pReadDeq, 0));
	CHKiRet(strm.ConstructFinalize(pThis->tVars.disk.pReadDeq));

	CHKiRet(strm.SeekCurrOffs(pThis->tVars.disk.pWrite));
	CHKiRet(strm.SeekCurrOffs(pThis->tVars.disk.pReadDel));
	CHKiRet(strm.SeekCurrOffs(pThis->tVars.disk.pReadDeq));


	pThis->bNeedDelQIF = 1;

finalize_it:
	if(psQIF != NULL)
		strm.Destruct(&psQIF);

	if(iRet != RS_RET_OK) {
		DBGOPRINT((obj_t*) pThis, "error %d reading .qi file - can not read persisted info (if any)\n",
			  iRet);
	}

	RETiRet;
}
