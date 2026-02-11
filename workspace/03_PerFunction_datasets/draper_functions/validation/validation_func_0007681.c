getZFromBelow(double currentZ, bool fromBelow) {
    double frac = currentZ - m_initialZ;
    if (qAbs(frac) > 1) {
        frac = currentZ - m_initialZFromBelow;
    }
    return frac + (fromBelow ? m_initialZFromBelow : m_initialZ);
}
