get_bg_pixmap(GP<DjVuImage> dimg, const GRect &rect)
{
  GP<GPixmap> pm = 0;

  int width = dimg->get_width();
  int height = dimg->get_height();
  GP<DjVuInfo> info = dimg->get_info();
  if (width<=0 || height<=0 || !info) return 0;

  GP<IW44Image> bg44 = dimg->get_bg44();
  if (bg44)
    {
      int w = bg44->get_width();
      int h = bg44->get_height();

      if (w==0 || h==0 || width==0 || height==0)
        return 0;
      pm = bg44->get_pixmap(1,rect);
      return pm;
    }

  GP<GPixmap>  bgpm = dimg->get_bgpm();
  if (bgpm)
    {
      int w = bgpm->columns();
      int h = bgpm->rows();

      if (w==0 || h==0 || width==0 || height==0)
        return 0;
      pm->init(*bgpm, rect);
      return pm;
    }

  return 0;
}
