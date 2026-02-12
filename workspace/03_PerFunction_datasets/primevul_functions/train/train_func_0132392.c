void PCM::runPush()
{
	AFframecount frames2write = m_inChunk->frameCount;
	AFframecount n;


	ssize_t bytesWritten = write(m_inChunk->buffer, m_bytesPerFrame * frames2write);
	n = bytesWritten >= 0 ? bytesWritten / m_bytesPerFrame : 0;

	CHNK(printf("writing %" AF_FRAMECOUNT_PRINT_FMT " frames to pcm file\n",
		frames2write));

	if (n != frames2write)
	{

		if (m_track->filemodhappy)
		{

			if (n < 0)
				_af_error(AF_BAD_WRITE,
					"unable to write data (%s) -- "
					"wrote %d out of %d frames",
					strerror(errno),
					m_track->nextfframe + n,
					m_track->nextfframe + frames2write);

			else
				_af_error(AF_BAD_WRITE,
					"unable to write data (disk full) -- "
					"wrote %d out of %d frames",
					m_track->nextfframe + n,
					m_track->nextfframe + frames2write);
			m_track->filemodhappy = false;
		}
	}

	m_track->nextfframe += n;
	m_track->totalfframes = m_track->nextfframe;
	m_track->fpos_next_frame += (n>0) ? n * m_bytesPerFrame : 0;
	assert(!canSeek() || (tell() == m_track->fpos_next_frame));
}
