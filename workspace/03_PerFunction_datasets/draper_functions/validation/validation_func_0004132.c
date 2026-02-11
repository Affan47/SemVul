getColor (unsigned int iCurve) const

{

  if (m_veciColor.size() > iCurve && m_vecbColorSet[iCurve])

    return m_veciColor[iCurve];

  else

    return o_color;

}
