php_image_filter_edgedetect(gdImagePtr im, int  ,
                            int  , int  ,
                            int  ) {
  return gdImageEdgeDetectQuick(im) == 1;
}
