String(size_t cap, ReserveStringMode )
      : m_str(StringData::Make(cap), NoIncRef{}) {}
