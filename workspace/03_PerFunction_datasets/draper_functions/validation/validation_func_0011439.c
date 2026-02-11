ContainsData(const BrickKey &k, double fMin,double fMax) const
{

  if(NULL == m_timesteps[std::get<0>(k)]->m_pMaxMinData) {return true;}
  const InternalMaxMinComponent maxMinElement = MaxMinForKey(k);
  return (fMax >= maxMinElement.minScalar && fMin <= maxMinElement.maxScalar);
}
