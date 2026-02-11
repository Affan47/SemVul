parseMiscellaneous(const Tag &type, size_t size)
{
	int misctype = AF_MISC_UNRECOGNIZED;

	assert(type == "NAME" ||
		type == "AUTH" ||
		type == "(c) " ||
		type == "ANNO" ||
		type == "APPL" ||
		type == "MIDI");


	if (size == 0)
		return AF_FAIL;

	m_miscellaneousCount++;
	m_miscellaneous = (Miscellaneous *) _af_realloc(m_miscellaneous,
		m_miscellaneousCount * sizeof (Miscellaneous));

	if (type == "NAME")
		misctype = AF_MISC_NAME;
	else if (type == "AUTH")
		misctype = AF_MISC_AUTH;
	else if (type == "(c) ")
		misctype = AF_MISC_COPY;
	else if (type == "ANNO")
		misctype = AF_MISC_ANNO;
	else if (type == "APPL")
		misctype = AF_MISC_APPL;
	else if (type == "MIDI")
		misctype = AF_MISC_MIDI;

	m_miscellaneous[m_miscellaneousCount - 1].id = m_miscellaneousCount;
	m_miscellaneous[m_miscellaneousCount - 1].type = misctype;
	m_miscellaneous[m_miscellaneousCount - 1].size = size;
	m_miscellaneous[m_miscellaneousCount - 1].position = 0;
	m_miscellaneous[m_miscellaneousCount - 1].buffer = _af_malloc(size);
	m_fh->read(m_miscellaneous[m_miscellaneousCount - 1].buffer, size);

	return AF_SUCCEED;
}
