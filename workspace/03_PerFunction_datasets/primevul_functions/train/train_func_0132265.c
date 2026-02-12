void PCM::sync2()
{
	assert(!canSeek() || (tell() == m_track->fpos_next_frame));


	m_track->fpos_after_data = tell();

	m_track->fpos_next_frame = m_saved_fpos_next_frame;
	m_track->nextfframe = m_saved_nextfframe;
}
