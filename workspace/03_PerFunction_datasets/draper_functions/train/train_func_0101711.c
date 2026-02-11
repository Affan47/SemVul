animateVisibility(const bool visible)
{
    m_fade->setProperty("startOpacity", opacity());

    if (visible) {
        m_fade->setProperty("targetOpacity", 1.0);
    } else {
        m_fade->setProperty("targetOpacity", 0);
    }
    m_fade->start();
}
