getScanLineVert(short* red, short* green, short* blue,
					      float x1, float y1, float x2, float y2, int npixels) {
  src.getScanLineVert(red,green,blue,x1,y1,x2,y2,npixels);
  for (int i=0; i<npixels; ++i) {
    CONTRAST_ADJUST(red[i]);
    CONTRAST_ADJUST(green[i]);
    CONTRAST_ADJUST(blue[i]);
  }
}
