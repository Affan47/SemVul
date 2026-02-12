void HuffmanDecoder::Initialize(const unsigned int *codeBits, unsigned int nCodes)
{


	if (nCodes == 0)
		throw Err("null code");

	m_maxCodeBits = *std::max_element(codeBits, codeBits+nCodes);

	if (m_maxCodeBits > MAX_CODE_BITS)
		throw Err("code length exceeds maximum");

	if (m_maxCodeBits == 0)
		throw Err("null code");


	SecBlockWithHint<unsigned int, 15+1> blCount(m_maxCodeBits+1);
	std::fill(blCount.begin(), blCount.end(), 0);
	unsigned int i;
	for (i=0; i<nCodes; i++)
		blCount[codeBits[i]]++;


	code_t code = 0;
	SecBlockWithHint<code_t, 15+1> nextCode(m_maxCodeBits+1);
	nextCode[1] = 0;
	for (i=2; i<=m_maxCodeBits; i++)
	{

		if (code > code + blCount[i-1])
			throw Err("codes oversubscribed");
		code += blCount[i-1];
		if (code > (code << 1))
			throw Err("codes oversubscribed");
		code <<= 1;
		nextCode[i] = code;
	}


	const word64 shiftedMaxCode = ((word64)1 << m_maxCodeBits);
	if (code > shiftedMaxCode - blCount[m_maxCodeBits])
		throw Err("codes oversubscribed");
	else if (m_maxCodeBits != 1 && code < shiftedMaxCode - blCount[m_maxCodeBits])
		throw Err("codes incomplete");


	m_codeToValue.resize(nCodes - blCount[0]);
	unsigned int j=0;
	for (i=0; i<nCodes; i++)
	{
		unsigned int len = codeBits[i];
		if (len != 0)
		{
			code = NormalizeCode(nextCode[len]++, len);
			m_codeToValue[j].code = code;
			m_codeToValue[j].len = len;
			m_codeToValue[j].value = i;
			j++;
		}
	}
	std::sort(m_codeToValue.begin(), m_codeToValue.end());


	m_cacheBits = STDMIN(9U, m_maxCodeBits);
	m_cacheMask = (1 << m_cacheBits) - 1;
	m_normalizedCacheMask = NormalizeCode(m_cacheMask, m_cacheBits);
	CRYPTOPP_ASSERT(m_normalizedCacheMask == BitReverse(m_cacheMask));

	const word64 shiftedCache = ((word64)1 << m_cacheBits);
	CRYPTOPP_ASSERT(shiftedCache <= SIZE_MAX);
	if (m_cache.size() != shiftedCache)
		m_cache.resize((size_t)shiftedCache);

	for (i=0; i<m_cache.size(); i++)
		m_cache[i].type = 0;
}
