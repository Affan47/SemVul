GetSolutionValue(unsigned int i,
                                                                             unsigned int solutionIndex) const
{

  if( ( i >= m_Order ) || !m_Solutions || ( solutionIndex >= m_NumberOfSolutions ) || !( *m_Solutions )[solutionIndex] )
    {
    return 0.0;
    }
  return ( *m_Solutions )[solutionIndex][i];
}
