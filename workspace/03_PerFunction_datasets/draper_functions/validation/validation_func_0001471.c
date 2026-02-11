GenerateEngineCode(int , std::vector<gr::byte> & vbOutput,
	int iritCurrent, std::vector<int> * pviritInput, int ,
	bool , int , int * pnValue)
{
	int nOffset = m_nIOIndex - iritCurrent;

	Assert(!pviritInput);
	if (pviritInput)
		nOffset = (*pviritInput)[m_nIOIndex] - iritCurrent;

	char bOffset = (char)nOffset;
	Assert((int)bOffset == nOffset);


	*pnValue = nOffset;

	vbOutput.push_back(kopPushByte);
	vbOutput.push_back(bOffset);
}
