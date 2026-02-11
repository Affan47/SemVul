Create() {
  if (m_bFileIsLoaded) return false;

  m_bFileIsLoaded = m_streamFile->Create();

  if (m_bFileIsLoaded) {

    m_bFileIsReadWrite = true;

    unsigned char pData[8];
    pData[0] = 'U';
    pData[1] = 'V';
    pData[2] = 'F';
    pData[3] = '-';
    pData[4] = 'D';
    pData[5] = 'A';
    pData[6] = 'T';
    pData[7] = 'A';
    m_streamFile->WriteRAW(pData, 8);

    m_GlobalHeader.CopyHeaderToFile(m_streamFile);

    uint64_t iOffset = m_GlobalHeader.GetDataPos();
    for (size_t i = 0;i<m_DataBlocks.size();i++) {
        iOffset += m_DataBlocks[i]->m_block->CopyToFile(m_streamFile, iOffset,
                                                m_GlobalHeader.bIsBigEndian,
                                                i == m_DataBlocks.size()-1);
        m_DataBlocks[i]->m_bIsDirty = false;
    }

    return true;
  }else {
    return false;
  }
}
