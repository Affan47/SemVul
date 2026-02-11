CheckExist()
{
  size_t idx = 0;
  size_t percent = GetNPieces() / 100;
  unsigned char md[20];

  if( !percent ) percent = 1;

  CONSOLE.Interact_n("");
  for( ; idx < m_npieces; idx++ ){
    if( GetHashValue(idx, md) < 0 ){
      CONSOLE.Warning(1, "Error while checking piece %d of %d",
        (int)idx+1, (int)m_npieces);
      return -1;
    }
    if( memcmp(md, m_hash_table + idx * 20, 20) == 0 ){
       m_left_bytes -= GetPieceLength(idx);
       pBF->Set(idx);
    }
    if( idx % percent == 0 || idx == m_npieces-1 )
      CONSOLE.InteractU("Check exist: %d/%d", idx+1, m_npieces);
  }
  m_check_piece = m_npieces;
  pBChecked->SetAll();
  return 0;
}
