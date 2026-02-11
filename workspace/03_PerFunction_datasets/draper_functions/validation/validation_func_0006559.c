SetEncoderNumFastBytes(INT A) {
  INT aNumFastBytes = A;
  if(aNumFastBytes < 2 || aNumFastBytes > kMatchMaxLen)
    return E_INVALIDARG;

  m_NumFastBytes = aNumFastBytes;

  return S_OK;
}
