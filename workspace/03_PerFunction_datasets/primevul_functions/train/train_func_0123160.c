long long Block::GetTimeCode(const Cluster* pCluster) const {
  if (pCluster == 0)
    return m_timecode;

  const long long tc0 = pCluster->GetTimeCode();
  assert(tc0 >= 0);


  if (tc0 < 0 || LLONG_MAX - tc0 < m_timecode) {
    return -1;
  }

  const long long tc = tc0 + m_timecode;

  return tc;
}
