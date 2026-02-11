addCSSProperty(int id, int value)
{
    if (!m_hasCombinedStyle) createNonCSSDecl();
    nonCSSStyleDecls()->setProperty(id, value, false);
    setChanged();
}
