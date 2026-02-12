status WAVEFile::parseList(const Tag &id, uint32_t size)
{
	Tag typeID;
	readTag(&typeID);
	size-=4;

	if (typeID == "adtl")
	{

		return parseADTLSubChunk(typeID, size);
	}
	else if (typeID == "INFO")
	{

		return parseINFOSubChunk(typeID, size);
	}
	else
	{

		m_fh->seek(size, File::SeekFromCurrent);
		return AF_SUCCEED;
	}
	return AF_SUCCEED;
}
