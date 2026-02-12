status WAVEFile::writeCues()
{
	Track *track = getTrack();

	if (!track->markerCount)
		return AF_SUCCEED;

	if (m_markOffset == 0)
		m_markOffset = m_fh->tell();
	else
		m_fh->seek(m_markOffset, File::SeekFromBeginning);

	Tag cue("cue ");
	writeTag(&cue);


	uint32_t cueChunkSize = 4 + track->markerCount * 24;
	writeU32(&cueChunkSize);
	uint32_t numCues = track->markerCount;
	writeU32(&numCues);


	for (int i=0; i<track->markerCount; i++)
	{
		uint32_t identifier = track->markers[i].id;
		writeU32(&identifier);

		uint32_t position = i;
		writeU32(&position);

		Tag data("data");
		writeTag(&data);


		uint32_t chunkStart = 0;
		writeU32(&chunkStart);

		uint32_t blockStart = 0;
		writeU32(&blockStart);

		AFframecount markPosition = track->markers[i].position;
		uint32_t sampleOffset = markPosition;
		writeU32(&sampleOffset);
	}


	uint32_t listChunkSize = 4;
	for (int i=0; i<track->markerCount; i++)
	{
		const char *name = track->markers[i].name;
		const char *comment = track->markers[i].comment;


		listChunkSize += 12 + zStringLength(name);
		listChunkSize += 12 + zStringLength(comment);
	}

	Tag list("LIST");
	writeTag(&list);
	writeU32(&listChunkSize);
	Tag adtl("adtl");
	writeTag(&adtl);

	for (int i=0; i<track->markerCount; i++)
	{
		uint32_t cuePointID = track->markers[i].id;

		const char *name = track->markers[i].name;
		uint32_t labelSize = 4 + zStringLength(name);
		Tag lablTag("labl");
		writeTag(&lablTag);
		writeU32(&labelSize);
		writeU32(&cuePointID);
		writeZString(name);

		const char *comment = track->markers[i].comment;
		uint32_t noteSize = 4 + zStringLength(comment);
		Tag noteTag("note");
		writeTag(&noteTag);
		writeU32(&noteSize);
		writeU32(&cuePointID);
		writeZString(comment);
	}

	return AF_SUCCEED;
}
