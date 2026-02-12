static rsRetVal uncompressMessage(smsg_t *pMsg)
{
	DEFiRet;
	uchar *deflateBuf = NULL;
	uLongf iLenDefBuf;
	uchar *pszMsg;
	size_t lenMsg;

	assert(pMsg != NULL);
	pszMsg = pMsg->pszRawMsg;
	lenMsg = pMsg->iLenRawMsg;


	if(lenMsg > 0 && *pszMsg == 'z') {


		int ret;
		iLenDefBuf = glbl.GetMaxLine();
		CHKmalloc(deflateBuf = MALLOC(iLenDefBuf + 1));
		ret = uncompress((uchar *) deflateBuf, &iLenDefBuf, (uchar *) pszMsg+1, lenMsg-1);
		DBGPRINTF("Compressed message uncompressed with status %d, length: new %ld, old %d.\n",
		        ret, (long) iLenDefBuf, (int) (lenMsg-1));


		if(ret != Z_OK) {
			errmsg.LogError(0, NO_ERRCODE, "Uncompression of a message failed with return code %d "
			            "- enable debug logging if you need further information. "
				    "Message ignored.", ret);
			FINALIZE;
		}
		MsgSetRawMsg(pMsg, (char*)deflateBuf, iLenDefBuf);
	}
finalize_it:
	if(deflateBuf != NULL)
		free(deflateBuf);

	RETiRet;
}
