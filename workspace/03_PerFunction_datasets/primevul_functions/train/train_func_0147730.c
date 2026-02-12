uint64 KaxBlockGroup::GlobalTimecode() const
{
  assert(ParentCluster != NULL);
  KaxInternalBlock & MyBlock = *static_cast<KaxBlock *>(this->FindElt(EBML_INFO(KaxBlock)));
  return MyBlock.GlobalTimecode();

}
