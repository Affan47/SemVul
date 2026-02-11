recthull(const GRect &rect1, const GRect &rect2)
{
  if (rect1.isempty())
    {
      xmin = rect2.xmin;
      xmax = rect2.xmax;
      ymin = rect2.ymin;
      ymax = rect2.ymax;
      return !isempty();
    }
  if (rect2.isempty())
    {
      xmin = rect1.xmin;
      xmax = rect1.xmax;
      ymin = rect1.ymin;
      ymax = rect1.ymax;
      return !isempty();
    }
  xmin = imin(rect1.xmin, rect2.xmin);
  xmax = imax(rect1.xmax, rect2.xmax);
  ymin = imin(rect1.ymin, rect2.ymin);
  ymax = imax(rect1.ymax, rect2.ymax);
  return 1;
}
