crops(const pair& arg) const
  {
    const double x(arg.x1());
    const double y(arg.x2());
    return !(   (m_hmin <= x) && (x <= m_hmax)
	     && (m_vmin <= y) && (y <= m_vmax));
  }
