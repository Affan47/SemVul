get_coords( GList<int> & CoordList ) const
{
  for(int i = 0 ; i < points ; i++)
  {
    CoordList.append( xx[i] );
    CoordList.append( yy[i] );
  }
}
