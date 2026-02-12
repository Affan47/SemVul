status WAVEFile::update()
{
	Track *track = getTrack();

	if (track->fpos_first_frame != 0)
	{
		uint32_t dataLength, fileLength;


		writeFrameCount();


		m_fh->seek(m_dataSizeOffset, File::SeekFromBeginning);
		dataLength = (uint32_t) track->data_size;
		writeU32(&dataLength);


		fileLength = (uint32_t) m_fh->length();
		fileLength -= 8;

		m_fh->seek(4, File::SeekFromBeginning);
		writeU32(&fileLength);
	}


	writeMiscellaneous();


	writeCues();

	return AF_SUCCEED;
}
