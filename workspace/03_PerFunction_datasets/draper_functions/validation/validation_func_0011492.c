Resample(void* dest, const void* src, size_t src_size)
{
    if (m_Iwf.wBitsPerSample != m_Owf.wBitsPerSample
	|| m_Iwf.nChannels != m_Owf.nChannels
	|| (m_Iwf.nChannels != 1 && m_Iwf.nChannels != 2))
    {
#if 0
	cerr << "AudioQueue::resample()  unsupported resampling conversion!" << endl
	    << "From:  bps: " << m_Iwf.wBitsPerSample
	    << "  ch: " << m_Iwf.nChannels
	    << "  To:  bps: " << m_Owf.wBitsPerSample
	    << "  ch: " << m_Owf.nChannels << endl;
#endif
	return 0;
    }

    if (!m_pResampler || (int)m_pResampler->getBitsPerSample() != m_Owf.wBitsPerSample)
    {
	delete m_pResampler;

	m_pResampler = CreateHQResampler(m_Owf.nChannels, m_Owf.wBitsPerSample);

	if (!m_pResampler)
	{
	    AVM_WRITE("aviplay", "AudioQueue::resample()  creation of resampler failed\n");
	    return 0;
	}
    }
    double ndest_size = (double) src_size / m_Iwf.nSamplesPerSec * m_Owf.nSamplesPerSec
	/ (m_Owf.wBitsPerSample / 8 * m_Owf.nChannels);

    src_size /= (m_Iwf.wBitsPerSample / 8 * m_Iwf.nChannels);
    size_t dest_size = (size_t) ndest_size;

    m_dRemains += (ndest_size - (double)dest_size);
    if (m_dRemains > 1.0)
    {
	m_dRemains -= 1.0;
        dest_size++;
    }


    AVM_WRITE("aviplay", 2, "AudioQueue::resample()  freq: %" PRIsz "   ->   %" PRIsz "\n", src_size, dest_size);
    if (dest_size > 0)
	m_pResampler->resample(dest, src, dest_size, src_size);


    return (ssize_t) (dest_size * (m_Owf.wBitsPerSample / 8) * m_Owf.nChannels);
}
