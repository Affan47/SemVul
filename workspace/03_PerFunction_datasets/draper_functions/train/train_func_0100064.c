hasTransparency() const
{
  AttributeSeq os;
  iCascade->allNames(EOpacity, os);
  for (uint i = 0; i < os.size(); ++i) {
    Attribute val = iCascade->find(EOpacity, os[i]);
    if (val != Attribute::ONE())
      return true;
  }
  return false;
}
