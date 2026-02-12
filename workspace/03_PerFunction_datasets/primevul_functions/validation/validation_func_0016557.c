HRESULT Http::HrResponseBody(const std::string &strResponse)
{
	m_strRespBody += strResponse;

	return hrSuccess;
}
