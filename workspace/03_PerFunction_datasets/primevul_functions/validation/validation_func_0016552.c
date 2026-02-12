HRESULT HrParseURL(const std::string &strUrl, ULONG *lpulFlag, std::string *lpstrUrlUser, std::string *lpstrFolder)
{
	HRESULT hr = hrSuccess;
	std::string strService, strFolder, strUrlUser;
	ULONG ulFlag = 0;
	auto vcUrlTokens = tokenize(strUrl, L'/', true);
	decltype(vcUrlTokens)::const_iterator iterToken;
	if (vcUrlTokens.empty())

		goto exit;

	if (vcUrlTokens.back().rfind(".ics") != std::string::npos)

		vcUrlTokens.pop_back();
	else

		ulFlag |= REQ_COLLECTION;
	if (vcUrlTokens.empty())
		goto exit;
	if (vcUrlTokens.size() > 3) {

		hr = MAPI_E_TOO_COMPLEX;
		goto exit;
	}

	iterToken = vcUrlTokens.cbegin();

	strService = strToLower(*iterToken++);
	if (strService == "ical")
		ulFlag |= SERVICE_ICAL;
	else if (strService == "caldav")
		ulFlag |= SERVICE_CALDAV;
	else
		ulFlag |= SERVICE_UNKNOWN;
	if (iterToken == vcUrlTokens.cend())
		goto exit;


	strUrlUser = strToLower(*iterToken++);


	if (strUrlUser == "public")
		ulFlag |= REQ_PUBLIC;
	if (iterToken == vcUrlTokens.cend())
		goto exit;

	for (; iterToken != vcUrlTokens.end(); ++iterToken)
		strFolder = strFolder + *iterToken + "/";
	strFolder.erase(strFolder.length() - 1);
exit:
	if (lpulFlag)
		*lpulFlag = ulFlag;
	if (lpstrUrlUser)
		*lpstrUrlUser = std::move(strUrlUser);
	if (lpstrFolder)
		*lpstrFolder = std::move(strFolder);
	return hr;
}
