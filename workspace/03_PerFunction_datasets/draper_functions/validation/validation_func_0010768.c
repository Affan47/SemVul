allocateFields ( int x, int y, TerrainType::Weather* terrain )
{
   field = new MapField[x*y];
   for ( int i = 0; i < x*y; i++ ) {
      if ( terrain ) {
         field[i].typ = terrain;
         field[i].setparams();
      }
      field[i].setMap ( this );
   }
   xsize = x;
   ysize = y;
   overviewMapHolder.connect();
}
