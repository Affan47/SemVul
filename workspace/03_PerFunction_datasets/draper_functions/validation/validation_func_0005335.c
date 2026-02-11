extract(const P& arg1, const P& arg2) const
  {
    screen value(arg1, arg2);

    value.m_screen
      = new screen_data(m_screen->extract(pair(arg1.x1(), arg1.x2()),
					  pair(arg2.x1(), arg2.x2())));
    return value;
  }
