php_image_filter_grayscale(gdImagePtr im, int  ,
                           int  , int  ,
                           int  ) {
  return gdImageGrayScale(im) == 1;
}
