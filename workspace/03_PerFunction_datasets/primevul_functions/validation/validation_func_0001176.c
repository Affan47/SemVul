php_image_filter_pixelate(gdImagePtr im, int arg1 , int arg2 ,
                          int  , int  ) {
  int blocksize = arg1;
  unsigned mode = arg2;
  return gdImagePixelate(im, blocksize, mode) == 1;
}
