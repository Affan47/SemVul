toIndex(String str)
{
  assert(!str.isEmpty());
  std::vector<String>::const_iterator it =
    std::find(iStrings.begin(), iStrings.end(), str);
  if (it != iStrings.end())
    return (it - iStrings.begin());
  iStrings.push_back(str);
  return iStrings.size() - 1;
}
