inline const char* StringData::data() const {


#ifdef NO_M_DATA
  return reinterpret_cast<const char*>(this + 1);
#else
  return m_data;
#endif
}
