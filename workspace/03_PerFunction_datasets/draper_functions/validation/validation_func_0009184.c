operator>(const DateTime & dt) const
  {
    if(m_date.tv_sec == dt.m_date.tv_sec) {
      return (m_date.tv_usec > dt.m_date.tv_usec);
    }
    return (m_date.tv_sec > dt.m_date.tv_sec);
  }
