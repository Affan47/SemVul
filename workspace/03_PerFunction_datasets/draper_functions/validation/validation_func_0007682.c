Reset()
  {
    this->m_Events->SetItemNumber(0);
    this->m_Points->SetItemNumber(0);
    this->m_Analogs->SetItemNumber(0);
    this->m_FirstFrame = 1;
    this->m_PointFrequency = 0.0;
    this->m_PointFrameNumber = 0;
    this->m_AnalogSampleNumberPerPointFrame = 1;
    this->mp_MetaData = MetaData::New("ROOT");
    this->mp_MetaData->SetParent(this);
    this->m_AnalogResolution = Bit12;
    this->m_Units.resize(7,"");
    this->m_Units[Point::Marker] = "mm";
    this->m_Units[Point::Angle] = "deg";
    this->m_Units[Point::Force] = "N";
    this->m_Units[Point::Moment] = "Nmm";
    this->m_Units[Point::Power] = "W";
    this->m_Units[Point::Scalar] = "mm";
    this->m_Units[Point::Reaction] = "";
    this->m_MaxInterpolationGap = 10;
    this->Modified();
  }
