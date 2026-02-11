startGroup()
{
  if (m_collecting)
  {
    assert(m_layerOpened);
    assert(!m_objectsStack.empty());

    m_objectsStack.push(KEYObjectList_t());
    ++m_groupLevel;
  }
}
