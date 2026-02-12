fill_image_space(imglist * img)
{
  cattrflags attr0 = term.curs.attr.attr;

  term.curs.attr.imgi = img->imgi;
#ifdef debug_img_disp
  printf("fill %d:%d %d\n", term.curs.y, term.curs.x, img->imgi);
#endif

  short x0 = term.curs.x;
  if (term.sixel_display) {
    short y0 = term.curs.y;
    term.curs.y = 0;
    for (int y = 0; y < img->height && y < term.rows; ++y) {
      term.curs.y = y;
      term.curs.x = 0;

      for (int x = x0; x < x0 + img->width && x < term.cols; ++x)
        write_char(SIXELCH, 1);
    }
    term.curs.y = y0;
    term.curs.x = x0;
  } else {
    for (int i = 0; i < img->height; ++i) {
      term.curs.x = x0;

      for (int x = x0; x < x0 + img->width && x < term.cols; ++x)
        write_char(SIXELCH, 1);
      if (i == img->height - 1) {
        if (!term.sixel_scrolls_right) {
          write_linefeed();
          term.curs.x = term.sixel_scrolls_left ? 0: x0;
        }
      } else {
        write_linefeed();
      }
    }
  }

  term.curs.attr.attr = attr0;
}
