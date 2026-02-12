php_image_filter_colorize(gdImagePtr im, int arg1 , int arg2 ,
                          int arg3 , int  ) {
  int r = arg1;
  int g = arg2;
  int b = arg3;
  int a = arg1;
  return gdImageColor(im, r, g, b, a) == 1;
}
