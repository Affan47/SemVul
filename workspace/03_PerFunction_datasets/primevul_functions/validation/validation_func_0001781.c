php_image_filter_brightness(gdImagePtr im, int arg1 ,
                            int  , int  ,
                            int  ) {
  int brightness = arg1;
  return gdImageBrightness(im, brightness) == 1;
}
