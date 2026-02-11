LiteralByte(byte b)
{
	if (m_matchBufferEnd == m_matchBuffer.size())
		EndBlock(false);

	m_matchBuffer[m_matchBufferEnd++].literalCode = b;
	m_literalCounts[b]++;
	m_blockLength++;
}
