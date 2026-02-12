void PCM::runPull()
{
	AFframecount framesToRead = m_outChunk->frameCount;


	if (m_track->totalfframes != -1 &&
		m_track->nextfframe + framesToRead > m_track->totalfframes)
	{
		framesToRead = m_track->totalfframes - m_track->nextfframe;
	}

	ssize_t bytesRead = read(m_outChunk->buffer, m_bytesPerFrame * framesToRead);
	AFframecount framesRead = bytesRead >= 0 ? bytesRead / m_bytesPerFrame : 0;

	CHNK(printf("reading %" AF_FRAMECOUNT_PRINT_FMT " frames from pcm file "
		"(got %" AF_FRAMECOUNT_PRINT_FMT ")\n",
		framesToRead, framesRead));

	m_track->nextfframe += framesRead;
	m_track->fpos_next_frame += (framesRead>0) ? framesRead * m_bytesPerFrame : 0;
	assert(!canSeek() || (tell() == m_track->fpos_next_frame));


	if (framesRead != framesToRead && m_track->totalfframes != -1)
	{

		if (m_track->filemodhappy)
		{
			_af_error(AF_BAD_READ,
				"file missing data -- read %d frames, "
				"should be %d",
				m_track->nextfframe,
				m_track->totalfframes);
			m_track->filemodhappy = false;
		}
	}

	m_outChunk->frameCount = framesRead;
}
