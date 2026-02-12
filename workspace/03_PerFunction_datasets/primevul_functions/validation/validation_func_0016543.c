HRESULT Http::HrFinalize()
{
	HRESULT hr = hrSuccess;

	HrResponseHeader("Content-Length", stringify(m_strRespBody.length()));


	if (m_strRespBody.size() < HTTP_CHUNK_SIZE || m_strHttpVer != "1.1") {
		hr = HrFlushHeaders();
		if (hr != hrSuccess && hr != MAPI_E_END_OF_SESSION) {
			ec_log_debug("Http::HrFinalize flush fail %d", hr);
			m_ulRetCode = 0;
			return hr;
		}
		if (!m_strRespBody.empty()) {
			m_lpChannel->HrWriteString(m_strRespBody);
			ec_log_debug("Response body:\n%s", m_strRespBody.c_str());
		}
	}
	else
	{
		const char *lpstrBody = m_strRespBody.data();
		char lpstrLen[10];
		auto szBodyLen = m_strRespBody.size();
		size_t szBodyWritten = 0;
		unsigned int szPart = HTTP_CHUNK_SIZE;

		HrResponseHeader("Transfer-Encoding", "chunked");
		hr = HrFlushHeaders();
		if (hr != hrSuccess && hr != MAPI_E_END_OF_SESSION) {
			ec_log_debug("Http::HrFinalize flush fail(2) %d", hr);
			m_ulRetCode = 0;
			return hr;
		}

		while (szBodyWritten < szBodyLen)
		{
			if ((szBodyWritten + HTTP_CHUNK_SIZE) > szBodyLen)
				szPart = szBodyLen - szBodyWritten;

			snprintf(lpstrLen, sizeof(lpstrLen), "%X", szPart);
			m_lpChannel->HrWriteLine(lpstrLen);
			m_lpChannel->HrWriteLine(string_view(lpstrBody, szPart));
			szBodyWritten += szPart;
			lpstrBody += szPart;
		}


		snprintf(lpstrLen, 10, "0\r\n");
		m_lpChannel->HrWriteLine(lpstrLen);

		ec_log_debug("%s", m_strRespBody.c_str());
	}


	char szTime[32];
	time_t now = time(NULL);
	tm local;
	std::string strAgent;
	localtime_r(&now, &local);

	strftime(szTime, ARRAY_SIZE(szTime), "%d/%b/%Y:%H:%M:%S %z", &local);
	HrGetHeaderValue("User-Agent", &strAgent);
	ec_log_notice("%s - %s [%s] \"%s\" %d %d \"-\" \"%s\"", m_lpChannel->peer_addr(), m_strUser.empty() ? "-" : m_strUser.c_str(), szTime, m_strAction.c_str(), m_ulRetCode, (int)m_strRespBody.length(), strAgent.c_str());
	m_ulRetCode = 0;
	return hr;
}
