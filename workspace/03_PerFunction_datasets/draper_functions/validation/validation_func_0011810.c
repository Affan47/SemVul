Add(Hypothesis *hypo)
{
  std::pair<iterator, bool> ret = m_hypos.insert(hypo);

  if (ret.second) {

    VERBOSE(3,"added hyp to stack");


    if (hypo->GetTotalScore() > m_bestScore) {
      VERBOSE(3,", best on stack");
      m_bestScore = hypo->GetTotalScore();

      if ( m_bestScore + m_beamWidth > m_worstScore )
        m_worstScore = m_bestScore + m_beamWidth;
    }


    VERBOSE(3,", now size " << m_hypos.size());
    if (m_hypos.size() > 2*m_maxHypoStackSize-1) {
      PruneToSize(m_maxHypoStackSize);
    } else {
      VERBOSE(3,std::endl);
    }
  }

  return ret;
}
