internal_readFromStream(mrpt::utils::CStream &in)
{
	uint8_t version;
	in >> version;
	switch (version)
	{
	case 0:
		in >> refDistance >> m_alphaValuesCount >> m_score_priority;
		break;
	default:
		MRPT_THROW_UNKNOWN_SERIALIZATION_VERSION(version)
	};
}
