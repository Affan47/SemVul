TruncateCLOG(TransactionId oldestXact)
{
	int			cutoffPage;


	cutoffPage = TransactionIdToPage(oldestXact);


	if (!SlruScanDirectory(ClogCtl, SlruScanDirCbReportPresence, &cutoffPage))
		return;


	WriteTruncateXlogRec(cutoffPage);


	SimpleLruTruncate(ClogCtl, cutoffPage);
}
