inline bool StringData::same(const StringData* s) const {
  assertx(s);
  if (m_len != s->m_len) return false;


  assertx(uintptr_t(data()) % 8 == 0);
  assertx(uintptr_t(s->data()) % 8 == 0);
  return wordsame(data(), s->data(), m_len);
}
