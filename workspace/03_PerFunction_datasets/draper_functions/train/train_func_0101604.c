LastFirstFunc(unsigned L_idx)
{
  int fIdx(-1);

  unsigned word = m_L->at(L_idx);
  if((fIdx = F_firstIdx(word)) != -1) {

    fIdx += Rank(word, L_idx);
  }
  return fIdx;
}
