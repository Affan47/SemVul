affectedByNoInherit() const
{
    if (m_render && m_render->style())
        return m_render->style()->inheritedNoninherited();
    else
        return false;
}
