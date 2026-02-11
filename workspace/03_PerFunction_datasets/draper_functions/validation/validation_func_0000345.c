operator<(const MetalinkHttpEntry& rhs) const
{
  if(pref^rhs.pref) {
    return pref;
  } else {
    return pri < rhs.pri;
  }
}
