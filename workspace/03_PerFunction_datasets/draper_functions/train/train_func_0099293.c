toFull (gunichar ch)
{
    for (guint i = 0; i < G_N_ELEMENTS (m_table); i++) {
        if (G_UNLIKELY (ch < m_table[i][0]))
            return ch;
        if (G_UNLIKELY (ch < m_table[i][0] + m_table[i][2]))
            return ch - m_table[i][0] + m_table[i][1];
    }
    return ch;
}
