allocAlpha(unsigned char alpha) {
#ifdef HAVE_XRENDER
    if (m_source == 0 || !s_render)
        return;
    if (m_alpha_pic != 0)
        freeAlpha();

    m_alpha_pic = createAlphaPic(m_source, alpha);
    m_alpha = alpha;
#endif
}
