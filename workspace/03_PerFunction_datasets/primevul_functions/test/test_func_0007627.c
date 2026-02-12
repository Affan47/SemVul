bool HierarchicalBitmapRequester::isNextMCULineReady(void) const
{
#if ACCUSOFT_CODE


  return m_pSmallestScale->isNextMCULineReady();
#else
  return false;
#endif
}
