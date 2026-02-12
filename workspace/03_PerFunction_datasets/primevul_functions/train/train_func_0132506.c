void G711::sync2()
{

	assert(!canSeek() || (tell() == m_track->fpos_next_frame));


	m_track->fpos_after_data = tell();

	m_track->fpos_next_frame = m_savedPositionNextFrame;
	m_track->nextfframe = m_savedNextFrame;
}
