IsCompatible(const Phrase &inputPhrase, FactorType factorType) const
{
  if (inputPhrase.GetSize() != GetSize())	{
    return false;
  }
  for (size_t currPos = 0 ; currPos < GetSize() ; currPos++) {
    if (GetFactor(currPos, factorType) != inputPhrase.GetFactor(currPos, factorType))
      return false;
  }
  return true;
}
