drawSeparator(void)
{
  if (mapped()==MSTrue)
   {
     int offset=highlightThickness()+shadowThickness();
     int x=offset;
     int thickness=MSSashDefaultShadowThickness;
     if (thickness>1)
      {
	int y=height()>>1;
	XFillRectangle(display(),window(),bottomShadowGC(),
		       x,y,width()-2*offset,1);
	XFillRectangle(display(),window(),topShadowGC(),
		       x,y+1,width()-2*offset,1);
      }
     else
      {
	XFillRectangle(display(),window(),backgroundShadowGC(),
		       x,height()>>1,width()-2*offset,1);
      }
   }
}
