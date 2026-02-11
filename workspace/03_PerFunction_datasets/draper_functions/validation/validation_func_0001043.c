ucase (string s)
{
  for (uint i = 0; i < s.length(); i ++)
    s[i] = toupper (s[i]);
  return s;
}
