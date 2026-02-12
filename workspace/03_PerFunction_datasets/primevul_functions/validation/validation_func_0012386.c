static rsRetVal qqueuePersist(qqueue_t *pThis, int bIsCheckpoint)
{
	DEFiRet;
	strm_t *psQIF = NULL;
	uchar pszQIFNam[MAXFNAME];
	size_t lenQIFNam;

	ASSERT(pThis != NULL);

	if(pThis->qType != QUEUETYPE_DISK) {
		if(getPhysicalQueueSize(pThis) > 0) {


			ABORT_FINALIZE(RS_RET_NOT_IMPLEMENTED);
		} else
			FINALIZE;
	}

	DBGOPRINT((obj_t*) pThis, "persisting queue to disk, %d entries...\n", getPhysicalQueueSize(pThis));


	lenQIFNam = snprintf((char*)pszQIFNam, sizeof(pszQIFNam) / sizeof(uchar), "%s/%s.qi",
			     (char*) glbl.GetWorkDir(), (char*)pThis->pszFilePrefix);

	if((bIsCheckpoint != QUEUE_CHECKPOINT) && (getPhysicalQueueSize(pThis) == 0)) {
		if(pThis->bNeedDelQIF) {
			unlink((char*)pszQIFNam);
			pThis->bNeedDelQIF = 0;
		}

		if(pThis->tVars.disk.pReadDel != NULL)
			CHKiRet(strm.SetbDeleteOnClose(pThis->tVars.disk.pReadDel, 1));
		FINALIZE;
	}

	CHKiRet(strm.Construct(&psQIF));
	CHKiRet(strm.SettOperationsMode(psQIF, STREAMMODE_WRITE_TRUNC));
	CHKiRet(strm.SetbSync(psQIF, pThis->bSyncQueueFiles));
	CHKiRet(strm.SetsType(psQIF, STREAMTYPE_FILE_SINGLE));
	CHKiRet(strm.SetFName(psQIF, pszQIFNam, lenQIFNam));
	CHKiRet(strm.ConstructFinalize(psQIF));


	CHKiRet(obj.BeginSerializePropBag(psQIF, (obj_t*) pThis));
	objSerializeSCALAR(psQIF, iQueueSize, INT);
	objSerializeSCALAR(psQIF, tVars.disk.sizeOnDisk, INT64);
	objSerializeSCALAR(psQIF, tVars.disk.bytesRead, INT64);
	CHKiRet(obj.EndSerialize(psQIF));


	CHKiRet(strm.Serialize(pThis->tVars.disk.pWrite, psQIF));
	CHKiRet(strm.Serialize(pThis->tVars.disk.pReadDel, psQIF));


	if(bIsCheckpoint != QUEUE_CHECKPOINT) {
		CHKiRet(strm.SetbDeleteOnClose(pThis->tVars.disk.pReadDel, 0));
	}


	pThis->bNeedDelQIF = 1;

finalize_it:
	if(psQIF != NULL)
		strm.Destruct(&psQIF);

	RETiRet;
}
