php_image_filter_contrast(gdImagePtr im, int arg1 ,
                          int  , int  ,
                          int  ) {
  int contrast = arg1;
  return gdImageContrast(im, contrast) == 1;
}
