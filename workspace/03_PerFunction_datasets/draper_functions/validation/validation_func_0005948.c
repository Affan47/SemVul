NP_marshalComplexParams(cdrStream& s,
					   TypeCode_offsetTable* tbl) const
{
  OMNIORB_ASSERT(pd_resolved);
  pd_resolved->NP_marshalComplexParams(s, tbl);
}
