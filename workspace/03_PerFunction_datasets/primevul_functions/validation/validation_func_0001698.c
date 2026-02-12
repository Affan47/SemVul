php_image_filter_selective_blur(gdImagePtr im, int  ,
                                int  , int  ,
                                int  ) {
  return gdImageSelectiveBlur(im) == 1;
}
