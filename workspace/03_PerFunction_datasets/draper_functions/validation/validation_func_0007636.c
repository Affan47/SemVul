operator==(const UString& s1, const UString& s2)
{
#if 0
  if (s1.m_rep == s2.m_rep)
    return true;
#endif

  if (s1.m_rep->len != s2.m_rep->len)
    return false;

  return (memcmp(s1.m_rep->data(), s2.m_rep->data(),
		 s1.m_rep->len * sizeof(UChar)) == 0);
}
