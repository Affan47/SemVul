links() const
{
  LinkExtractorOutputDev link_dev(m_page);
  m_page->parentDoc->doc->processLinks(&link_dev, m_page->index + 1);
  QList<Link*> popplerLinks = link_dev.links();

  return popplerLinks;
}
