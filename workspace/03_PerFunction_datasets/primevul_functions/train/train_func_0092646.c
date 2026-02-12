Error HeifContext::add_XMP_metadata(std::shared_ptr<Image> master_image, const void* data, int size)
{


  auto metadata_infe_box = m_heif_file->add_new_infe_box("mime");
  metadata_infe_box->set_content_type("application/rdf+xml");
  metadata_infe_box->set_hidden_item(true);

  heif_item_id metadata_id = metadata_infe_box->get_item_ID();


  m_heif_file->add_iref_reference(metadata_id,
                                  fourcc("cdsc"), { master_image->get_id() });


  std::vector<uint8_t> data_array;
  data_array.resize(size);
  memcpy(data_array.data(), data, size);

  m_heif_file->append_iloc_data(metadata_id, data_array);

  return Error::Ok;
}
