collectData(const boost::optional<ID_t> &id, const WPXInputStreamPtr_t &stream, const boost::optional<std::string> &displayName, const boost::optional<unsigned> &type, const bool ref)
{
  if (m_collecting)
  {
    KEYDataPtr_t newData;

    if (!ref)
    {
      newData.reset(new KEYData());
      newData->stream = stream;
      newData->displayName = displayName;
      newData->type = type;
    }

    assert(!m_currentData);
    m_currentData = getValue(id, newData, ref, m_dict.data);
  }
}
