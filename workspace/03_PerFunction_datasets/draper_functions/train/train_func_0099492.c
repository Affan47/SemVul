vfy_tag (vfy_constants *pool, int index)
{
  int result = JPOOL_TAG (pool, index);


  if ((result & CONSTANT_ResolvedFlag) != 0
      && result != CONSTANT_ResolvedString
      && result != CONSTANT_ResolvedClass)
    result &= ~ CONSTANT_ResolvedFlag;
  return result;
}
