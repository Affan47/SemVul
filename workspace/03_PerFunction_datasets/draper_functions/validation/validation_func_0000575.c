GetOOVWeight() const {
  if (m_enableOOVFeature) {

	return StaticData::Instance().GetWeights(this)[1];
  } else {
    return 0;
  }
}
