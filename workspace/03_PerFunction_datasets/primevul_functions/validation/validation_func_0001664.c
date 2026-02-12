inline bool StringData::isStrictlyInteger(int64_t& res) const {


  if ((unsigned char)(data()[0] - '-') > ('9' - '-')) {
    return false;
  }
  if (m_hash < 0) return false;
  auto const s = slice();
  return is_strictly_integer(s.data(), s.size(), res);
}
