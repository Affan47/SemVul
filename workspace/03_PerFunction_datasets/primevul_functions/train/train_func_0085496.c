status WAVEFile::writeMiscellaneous()
{
	if (m_miscellaneousCount != 0)
	{
		uint32_t	miscellaneousBytes;
		uint32_t 	chunkSize;


		miscellaneousBytes = 12;


		for (int i=0; i<m_miscellaneousCount; i++)
		{
			Tag miscid;


			if (!misc_type_to_wave(m_miscellaneous[i].type, &miscid))
				continue;


			miscellaneousBytes += 8;
			miscellaneousBytes += m_miscellaneous[i].size;


			if (m_miscellaneous[i].size % 2 != 0)
				miscellaneousBytes++;

			assert(miscellaneousBytes % 2 == 0);
		}

		if (m_miscellaneousOffset == 0)
			m_miscellaneousOffset = m_fh->tell();
		else
			m_fh->seek(m_miscellaneousOffset, File::SeekFromBeginning);


		m_fh->write("LIST", 4);


		chunkSize = miscellaneousBytes-8;
		writeU32(&chunkSize);


		m_fh->write("INFO", 4);


		for (int i=0; i<m_miscellaneousCount; i++)
		{
			uint32_t miscsize = m_miscellaneous[i].size;
			Tag miscid;


			if (!misc_type_to_wave(m_miscellaneous[i].type, &miscid))
				continue;

			writeTag(&miscid);
			writeU32(&miscsize);
			if (m_miscellaneous[i].buffer != NULL)
			{
				uint8_t	zero = 0;

				m_fh->write(m_miscellaneous[i].buffer, m_miscellaneous[i].size);


				if ((m_miscellaneous[i].size%2) != 0)
					writeU8(&zero);
			}
			else
			{
				int	size;
				size = m_miscellaneous[i].size;


				if ((size % 2) != 0)
					size++;
				m_fh->seek(size, File::SeekFromCurrent);
			}
		}
	}

	return AF_SUCCEED;
}
