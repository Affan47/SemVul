GenerateEngineCode(GrcManager * , int fxdRuleVersion,
	std::vector<gr::byte> & vbOutput)
{
	if (m_vpexpConstraints.size() == 0)
	{
		return;
	}


	int nBogus;
	m_vpexpConstraints[0]->GenerateEngineCode(fxdRuleVersion, vbOutput,
		-1, NULL, -1, false, -1, &nBogus);
	for (size_t ipexp = 1; ipexp < m_vpexpConstraints.size(); ipexp++)
	{
		m_vpexpConstraints[ipexp]->GenerateEngineCode(fxdRuleVersion, vbOutput,
			-1, NULL, -1, false, -1, &nBogus);
		vbOutput.push_back(kopAnd);
	}
	vbOutput.push_back(kopPopRet);
}
