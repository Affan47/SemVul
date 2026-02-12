void HeifContext::set_primary_image(std::shared_ptr<Image> image)
{


  if (m_primary_image) {
    m_primary_image->set_primary(false);
  }

  image->set_primary(true);
  m_primary_image = image;


  m_heif_file->set_primary_item_id(image->get_id());
}
