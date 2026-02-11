addContent(const std::string &text, bool addLen)
{
  m_content += text;
  m_addContentLen = (m_addContentLen || addLen);
}
