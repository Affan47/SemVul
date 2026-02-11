ReportHashStl(std::basic_string<TCHAR>& strOut, REPORT_TYPE rtReportType) const
{
	TCHAR tszOut[84];
	const bool bResult = ReportHash(tszOut, rtReportType);
	if(bResult) strOut = tszOut;
	return bResult;
}
