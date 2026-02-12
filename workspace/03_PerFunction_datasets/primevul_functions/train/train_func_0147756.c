uint64 KaxInternalBlock::ClusterPosition() const
{
  assert(ParentCluster != NULL);
  return ParentCluster->GetPosition();
}
