Error Box_iloc::append_data(heif_item_id item_ID,
                            const std::vector<uint8_t>& data,
                            uint8_t construction_method)
{


  size_t idx;
  for (idx=0;idx<m_items.size();idx++) {
    if (m_items[idx].item_ID == item_ID) {
      break;
    }
  }


  if (idx == m_items.size()) {
    Item item;
    item.item_ID = item_ID;
    item.construction_method = construction_method;

    m_items.push_back(item);
  }

  if (m_items[idx].construction_method != construction_method) {

  }

  Extent extent;
  extent.data = data;
  m_items[idx].extents.push_back( std::move(extent) );

  return Error::Ok;
}
