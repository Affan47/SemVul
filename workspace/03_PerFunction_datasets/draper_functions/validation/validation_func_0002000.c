computeTableSegmentHeight(int rs_,int re_)
{
  int header=tableHeaderHeight()+tableFooterHeight();
  double scale=scaleHeaders()==MSTrue?y_printScale():1.0;
  int h=headingHeight()+tableTop()+tableBottom();
  for (unsigned i=rs_;i<re_;i++)
   {
     h+=rowHeights()(i)+rowLeadings()(i);
   }
  return (int)(h*y_printScale()+header*scale);
}
