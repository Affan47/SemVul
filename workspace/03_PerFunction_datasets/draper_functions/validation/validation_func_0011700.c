ReOpenRW() {
  if (IsInRWMode()) return true;


  m_pLargeRAWFile->Close();


  if (m_pLargeRAWFile->Open(true)) {


    m_pLargeRAWFile->Open(false);
    return false;
  }
  return true;
}
