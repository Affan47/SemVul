M(
  unsigned char *_m_
  )
{
  int i;
  unsigned char t0,t1,t2,t3;


  for( i=0; i<BLOCK_SIZE; i+=8 ){
    _m_[i+4] ^= _m_[i];
    _m_[i+5] ^= _m_[i+1];
    _m_[i+6] ^= _m_[i+2];
    _m_[i+7] ^= _m_[i+3];
  }


  for( i=0; i<8; i++ ){
    t0 = _m_[i];
    t1 = _m_[i+8];
    t2 = _m_[i+16];
    t3 = _m_[i+24];

    _m_[i]  = t0 ^ t1 ^ t3;
    _m_[i+ 8] = t1 ^ t2 ^ t0;
    _m_[i+16] = t2 ^ t3 ^ t1;
    _m_[i+24] = t3 ^ t0 ^ t2;
  }
}
