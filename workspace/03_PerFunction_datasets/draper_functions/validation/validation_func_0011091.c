getPixel(float x1, float y1, float x2, float y2) {
  TransformCoordinates(x1,y1);
  TransformCoordinates(x2,y2);

  int ix1 = (int)floor(x1);
  int ix2 = (int)floor(x2);
  int iy1 = (int)floor(y1);
  int iy2 = (int)floor(y2);

  if (ix1<0) ix1=0;
  else if (ix1>=w-1) ix1=w-2;
  if (iy1<0) iy1=0;
  else if (iy1>=h-1) iy1=h-2;
  if (ix2<0) ix2=0;
  else if (ix2>=w-1) ix2=w-2;
  if (iy2<0) iy2=0;
  else if (iy2>=h-1) iy2=h-2;

  double result=0;
  double by1 = y1-iy1;
  for (int y=iy1; y<=iy2; ++y) {
    double by2 = y2-y;
    if ((y<(h-2))&&(by2>1)) by2=1;
    double sy = by2+by1;
    double dy = by2-by1;
    double bx1 = x1-ix1;

    for (int x=ix1; x<=ix2; ++x) {
      double bx2 = x2-x;
      if ((x<(w-2))&&(bx2>1)) bx2=1;
      double sx = bx2+bx1;
      double dx = bx2-bx1;

      result += ( (sx-2)*(sy-2)*tl[y*w+x]
		  -sx*(sy-2)*tl[y*w+x+1]
		  -(sx-2)*sy*tl[(y+1)*w+x]
		  +sx*sy*tl[(y+1)*w+x+1]
		  )*dx*dy;
      bx1=0;
    }
    by1=0;
  }
  return ((int)(result/(x2-x1)/(y2-y1)))/4;
}
