FillDimensions(const std::vector<std::string>& val)
  {
    this->m_Dims = std::vector<uint8_t>(2,0);
    this->m_Dims[1] = static_cast<uint8_t>(val.size());
    for (int i = 0 ; i < this->m_Dims[1] ; ++i)
    {
      int len = static_cast<int>(val[i].length());
      if (len > this->m_Dims[0])
        this->m_Dims[0] = len;
    }
  }
