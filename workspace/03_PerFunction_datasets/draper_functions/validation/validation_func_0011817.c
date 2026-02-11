PenDown( double x, double y, wxDC &dc )
{


  double xmin, ymin, xmax, ymax;
  ExGlobals::GetClippingBoundary( xmin, ymin, xmax, ymax );
  if( x>=xmin && xPrevious_>=xmin && x<=xmax && xPrevious_<=xmax &&
      y>=ymin && yPrevious_>=ymin && y<=ymax && yPrevious_<=ymax )
  {


    int ix, iy, ixp, iyp;
    WorldToOutputType( x, y, ix, iy );
    WorldToOutputType( xPrevious_, yPrevious_, ixp, iyp );
    dc.DrawLine( ixp, iyp, ix, iy );
  }
  else
  {
    int ndraw = 1;
    double xdraw[2], ydraw[2];
    xdraw[0] = x;
    ydraw[0] = y;
    UsefulFunctions::WindowClip( xPrevious_, yPrevious_, x, y,
                                 xmin, xmax, ymin, ymax,
                                 xdraw, ydraw, ndraw );
    switch (ndraw)
    {
      case 1:
      {
        int ix, iy, ixp, iyp;
        WorldToOutputType( xPrevious_, yPrevious_, ixp, iyp );
        WorldToOutputType( xdraw[0], ydraw[0], ix, iy );
        dc.DrawLine( ixp, iyp, ix, iy );
        break;
      }
      case 2:
      case 3:
      {
        int ix, iy, ixp, iyp;
        WorldToOutputType( xdraw[0], ydraw[0], ixp, iyp );
        WorldToOutputType( xdraw[1], ydraw[1], ix, iy );
        dc.DrawLine( ixp, iyp, ix, iy );
        break;
      }
    }
  }
  xPrevious_ = x;
  yPrevious_ = y;
  penPrevious_ = 2;
}
