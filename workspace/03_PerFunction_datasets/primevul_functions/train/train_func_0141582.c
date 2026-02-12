int Box_clap::left_rounded(int image_width) const
{


  Fraction pcX  = m_horizontal_offset + Fraction(image_width-1, 2);
  Fraction left = pcX - (m_clean_aperture_width-1)/2;

  return left.round();
}
