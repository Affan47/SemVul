PreallocXlogFiles(XLogRecPtr endptr)
{
	int			nsegsadded = 0;
	uint32		_logId;
	uint32		_logSeg;
	int			lf;
	bool		use_existent;

	XLByteToPrevSeg(endptr, _logId, _logSeg);
	if ((endptr.xrecoff - 1) % XLogSegSize >=
		(uint32) (0.75 * XLogSegSize))
	{
		NextLogSeg(_logId, _logSeg);
		use_existent = true;
		lf = XLogFileInit(_logId, _logSeg, &use_existent, true);
		close(lf);
		if (!use_existent)
			nsegsadded++;
	}
	return nsegsadded;
}
