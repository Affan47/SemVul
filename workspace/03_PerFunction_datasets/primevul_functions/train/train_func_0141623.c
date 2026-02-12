void Box_iloc::derive_box_version()
{
  int min_version = m_user_defined_min_version;

  if (m_items.size() > 0xFFFF) {
    min_version = std::max(min_version, 2);
  }

  m_offset_size = 0;
  m_length_size = 0;
  m_base_offset_size = 0;
  m_index_size = 0;

  for (const auto& item : m_items) {

    if (item.item_ID > 0xFFFF) {
      min_version = std::max(min_version, 2);
    }


    if (item.construction_method != 0) {
      min_version = std::max(min_version, 1);
    }


  }

  m_offset_size = 4;
  m_length_size = 4;
  m_base_offset_size = 4;
  m_index_size = 0;

  set_version((uint8_t)min_version);
}
