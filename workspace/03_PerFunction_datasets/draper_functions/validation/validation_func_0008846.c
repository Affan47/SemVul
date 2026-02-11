RGB2HSV( const DByte r, const DByte g, const DByte b,
	      DFloat& h, DFloat& s, DFloat& v )
{
  DByte cmin = (r < g)? ((r < b)? r : b) : ((g < b)? g : b);
  DByte cmax = (r > g)? ((r > b)? r : b) : ((g > b)? g : b);

  v = static_cast<DFloat>(cmax) / maxDByte;

  DFloat delta = static_cast<DFloat>(cmax - cmin);

  if( cmax != 0)
    s = delta / static_cast<DFloat>(cmax);
  else
    {

      s = 0.0;
      h = 0.0;
      return;
    }

  if( s == 0.0)
    {
      h = 0.0;
      return;
    }

  if( r == cmax )
    h = static_cast<DFloat>( g - b) / delta;
  else if( g == cmax )
    h = 2.0 + static_cast<DFloat>( b - r) / delta;
  else
    h = 4.0 + static_cast<DFloat>( r - g) / delta;

  h *= 60.0;
  if( h < 0.0 )
    h += 360.0;
}
