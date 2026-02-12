php_image_filter_smooth(gdImagePtr im, int arg1 ,
                        int  , int  ,
                        int  ) {
  int weight = arg1;
  return gdImageSmooth(im, weight) == 1;
}
