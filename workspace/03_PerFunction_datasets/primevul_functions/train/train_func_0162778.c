EmbFile::EmbFile(Object &&efStream)
{
  m_size = -1;
  m_createDate = nullptr;
  m_modDate = nullptr;
  m_checksum = nullptr;
  m_mimetype = nullptr;

  m_objStr = std::move(efStream);

  if (m_objStr.isStream()) {

    Dict *dataDict = m_objStr.streamGetDict();


    Object subtypeName = dataDict->lookup("Subtype");
    if (subtypeName.isName()) {
      m_mimetype = new GooString(subtypeName.getName());
    }


    Object paramDict = dataDict->lookup("Params");
    if (paramDict.isDict()) {
      Object paramObj = paramDict.dictLookup("ModDate");
      if (paramObj.isString())
        m_modDate = new GooString(paramObj.getString());

      paramObj = paramDict.dictLookup("CreationDate");
      if (paramObj.isString())
        m_createDate = new GooString(paramObj.getString());

      paramObj = paramDict.dictLookup("Size");
      if (paramObj.isInt())
        m_size = paramObj.getInt();

      paramObj = paramDict.dictLookup("CheckSum");
      if (paramObj.isString())
        m_checksum = new GooString(paramObj.getString());
    }
  }
}
