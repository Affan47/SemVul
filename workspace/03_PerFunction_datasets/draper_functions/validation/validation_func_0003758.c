draw_area(double scale) const
    {
      if (EPIX_EPSILON < m_hi - m_lo)
	rect(P(m_lo,0), P(m_hi, 0.5*scale*m_dbl_count/(m_hi - m_lo)));
    }
