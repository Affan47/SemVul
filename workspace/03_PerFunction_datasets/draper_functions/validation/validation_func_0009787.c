ElementData(void * _elementData, bool _autoFreeElementData)
  {
  if(m_AutoFreeElementData)
    {
    delete [] (char *)m_ElementData;
    }
  m_ElementData = _elementData;
  m_AutoFreeElementData = _autoFreeElementData;
  }
