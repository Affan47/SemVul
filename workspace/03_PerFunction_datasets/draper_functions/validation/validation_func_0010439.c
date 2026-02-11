realIndex(const QString& name)
{
  for (int i=0;i<_realCount;i++)
    if (_real[i] && (_real[i]->name() == name))
      return i;

  return ProfileCostArray::InvalidIndex;
}
