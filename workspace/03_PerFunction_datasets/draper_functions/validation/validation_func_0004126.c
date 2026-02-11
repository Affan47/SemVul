GetWeightDistortion() const {
      CHECK(m_distortionScoreProducer);
      return StaticData::Instance().GetWeight(m_distortionScoreProducer);
    }
