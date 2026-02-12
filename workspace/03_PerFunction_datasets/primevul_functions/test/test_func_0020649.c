doZipFinish(ptcpsess_t *pSess)
{
	int zRet;
	DEFiRet;
	unsigned outavail;
	struct syslogTime stTime;
	uchar zipBuf[32*1024];

	if(!pSess->bzInitDone)
		goto done;

	pSess->zstrm.avail_in = 0;

	do {
		DBGPRINTF("doZipFinish: in inflate() loop, avail_in %d, total_in %ld\n", pSess->zstrm.avail_in,
		pSess->zstrm.total_in);
		pSess->zstrm.avail_out = sizeof(zipBuf);
		pSess->zstrm.next_out = zipBuf;
		zRet = inflate(&pSess->zstrm, Z_FINISH);
		DBGPRINTF("after inflate, ret %d, avail_out %d\n", zRet, pSess->zstrm.avail_out);
		outavail = sizeof(zipBuf) - pSess->zstrm.avail_out;
		if(outavail != 0) {
			pSess->pLstn->rcvdDecompressed += outavail;
			CHKiRet(DataRcvdUncompressed(pSess, (char*)zipBuf, outavail, &stTime, 0));
		}
	} while (pSess->zstrm.avail_out == 0);

finalize_it:
	zRet = inflateEnd(&pSess->zstrm);
	if(zRet != Z_OK) {
		DBGPRINTF("imptcp: error %d returned from zlib/inflateEnd()\n", zRet);
	}

	pSess->bzInitDone = 0;
done:	RETiRet;
}
