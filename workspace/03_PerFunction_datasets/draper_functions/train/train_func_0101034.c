InitializeEssential(int _length,
                    MET_ValueEnumType _elementType,
                    int _elementNumberOfChannels,
                    void * _elementData,
                    bool _allocateElementData,
                    bool _autoFreeElementData)
  {
  if(META_DEBUG)
    {
    METAIO_STREAM::cout << "MetaArray: Initialize" << METAIO_STREAM::endl;
    }

  MetaForm::InitializeEssential();

  bool result = true;

  if(m_Length != _length ||
     m_ElementType != _elementType ||
     m_ElementNumberOfChannels != _elementNumberOfChannels ||
     _elementData != NULL ||
     _allocateElementData == true)
    {
    if(m_AutoFreeElementData)
      {
      if(m_ElementData != NULL)
        {
        delete [] (char *)m_ElementData;
        }
      }
    m_ElementData = NULL;

    m_Length = _length;
    m_ElementType = _elementType;
    m_ElementNumberOfChannels = _elementNumberOfChannels;

    if(_elementData != NULL)
      {
      m_ElementData = (void *)_elementData;
      }
    else
      {
      if(_allocateElementData)
        {
        result = AllocateElementData(_autoFreeElementData);
        }
      else
        {
        m_ElementData = NULL;
        }
      }

    m_AutoFreeElementData = _autoFreeElementData;
    }

  return result;
  }
