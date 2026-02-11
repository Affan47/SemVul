add(Animation* a)
{
    m_animations.enqueue(a);
    if (m_last != -1) {
        a->start(m_last);
    }
}
