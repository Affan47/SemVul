ShiftLeft(unsigned bits) throw()
{
	if ((bits == 0) || IsZero())
		return *this;

	if (bits > 127) {
		SetValue((uint32_t)0);
		return *this;
	}

	union {
		uint32_t u32_data[4];
		uint64_t u64_data[2];
	} result = {{ 0, 0, 0, 0 }};
	int indexShift = (int)bits / 32;
	int64_t shifted = 0;
	for (int i = 3; i >= indexShift; i--)
	{
		shifted += ((int64_t)m_data.u32_data[3 - i]) << (bits % 32);
		result.u32_data[3 - i + indexShift] = (uint32_t)shifted;
		shifted = shifted >> 32;
	}
	m_data.u64_data[0] = result.u64_data[0];
	m_data.u64_data[1] = result.u64_data[1];

	return *this;
}
