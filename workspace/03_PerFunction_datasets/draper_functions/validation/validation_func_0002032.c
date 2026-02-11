GetSortedList() const
{
  vector<const Hypothesis*> ret;
  ret.reserve(m_hypos.size());
  std::copy(m_hypos.begin(), m_hypos.end(), std::inserter(ret, ret.end()));
  sort(ret.begin(), ret.end(), CompareHypothesisTotalScore());

  return ret;
}
