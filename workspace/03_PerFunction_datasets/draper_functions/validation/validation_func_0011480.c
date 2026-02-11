Expand(const TranslationOption& topt, Scores& scores) const
{
  LexicalReorderingState *newbwd = m_backward->Expand(topt, scores);
  LexicalReorderingState *newfwd = m_forward->Expand(topt, scores);
  return new BidirectionalReorderingState(m_configuration, newbwd, newfwd, m_offset);
}
