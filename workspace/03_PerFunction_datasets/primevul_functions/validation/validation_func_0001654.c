php_image_filter_mean_removal(gdImagePtr im, int  ,
                              int  , int  ,
                              int  ) {
  return gdImageMeanRemoval(im) == 1;
}
