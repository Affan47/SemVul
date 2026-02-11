print (std::ostream& os) const
{
  if (m_labelType == L_HISTORY) {
    os << "History: " << std::endl;
    os << "  " << m_strLabel << std::endl;
    os << "  calc time = " << m_calcTime << " secs" << std::endl;
    os << "  Timestamp = " << getDateString() << std::endl;
  } else if (m_labelType == L_USER) {
    os << "Note: " <<  m_strLabel << std::endl;
    os << "  Timestamp = %s" << getDateString() << std::endl;
  } else {
    os << "Unknown (" << m_labelType << "): " <<  m_strLabel << std::endl;
    os << "  Timestamp = %s" << getDateString() << std::endl;
  }
}
