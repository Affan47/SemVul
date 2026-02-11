m_get_discrete_range(pIIR_Attr_ArrayREVERSE_RANGE atr, RegionStack &rstack, IR_StaticLevel slevel)
{
  vector<RangeDescriptor> bounds;
  bounds.push_back(RangeDescriptor(atr));

  return bounds;
}
