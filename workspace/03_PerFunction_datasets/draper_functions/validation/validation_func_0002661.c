insertDeferredLineBreaks()
{
  assert(bool(m_currentParagraph));

  if (0 < m_lineBreaks)
  {
    const KEYObjectPtr_t object(new LineBreakObject(m_currentParagraph->style));
    m_currentParagraph->objects.insert(m_currentParagraph->objects.end(), m_lineBreaks, object);
    m_lineBreaks = 0;
  }
}
