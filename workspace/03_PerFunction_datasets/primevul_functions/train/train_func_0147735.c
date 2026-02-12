uint64 KaxBlockGroup::ClusterPosition() const
{
  assert(ParentCluster != NULL);
  return ParentCluster->GetPosition();
}
