UnitCanReach( const Unit *u, const Point &pos, unsigned short dist ) {
  Path path(map);

  return (path.Find( u, u->Position(), pos, PATH_FAST, dist ) != -1) ||
         FindTransport( u, pos, dist, false );
}
