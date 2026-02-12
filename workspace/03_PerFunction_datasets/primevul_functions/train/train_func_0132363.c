void MSADPCM::runPull()
{
	AFframecount framesToRead = m_outChunk->frameCount;
	AFframecount framesRead = 0;

	assert(m_outChunk->frameCount % m_framesPerBlock == 0);
	int blockCount = m_outChunk->frameCount / m_framesPerBlock;


	ssize_t bytesRead = read(m_inChunk->buffer, m_blockAlign * blockCount);
	size_t blocksRead = bytesRead >= 0 ? bytesRead / m_blockAlign : 0;


	for (int i=0; i<blockCount; i++)
	{
		size_t bytesDecoded = decodeBlock(static_cast<const uint8_t *>(m_inChunk->buffer) + i * m_blockAlign,
			static_cast<int16_t *>(m_outChunk->buffer) + i * m_framesPerBlock * m_track->f.channelCount);

		framesRead += m_framesPerBlock;
	}

	m_track->nextfframe += framesRead;

	if (blocksRead > 0)
		m_track->fpos_next_frame += blocksRead * m_blockAlign;

	assert(tell() == m_track->fpos_next_frame);


	if (m_track->totalfframes != -1 && framesRead != framesToRead)
	{

		if (m_track->filemodhappy)
		{
			_af_error(AF_BAD_READ,
				"file missing data -- read %d frames, should be %d",
				m_track->nextfframe,
				m_track->totalfframes);
			m_track->filemodhappy = false;
		}
	}

	m_outChunk->frameCount = framesRead;
}
