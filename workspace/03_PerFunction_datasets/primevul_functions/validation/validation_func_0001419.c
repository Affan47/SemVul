php_image_filter_gaussian_blur(gdImagePtr im, int  ,
                               int  , int  ,
                               int  ) {
  return gdImageGaussianBlur(im) == 1;
}
