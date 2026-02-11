GeometryHasChanged(bool bUpdateAABB, bool bUpdateKDtree) {
  if (bUpdateAABB) ComputeAABB();
  if (bUpdateKDtree && m_KDTree) ComputeKDTree();
}
