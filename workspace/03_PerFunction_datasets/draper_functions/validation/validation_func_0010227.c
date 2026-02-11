processYUVImage(imageStruct &image)
{
  unsigned char min=255, max=0;
  int datasize = image.xsize * image.ysize;
  unsigned char *pixels = image.data;
  int n = datasize / 2;

  while(n--){

    unsigned char y0=pixels[chY0], y1=pixels[chY1];
    if (min>y0)  min=y0;
    if (min>y1)  min=y1;
    if (max<y0)  max=y0;
    if (max<y1)  max=y1;
    pixels+=4;
  }

  t_float scale=(max-min)?255./(max-min):0;
  int iscale=static_cast<int>(scale*256);


  n = datasize/2;
  pixels=image.data;
  while(n--){
    pixels[chY0] = static_cast<unsigned char>((pixels[chY0]-min)*iscale>>8);
    pixels[chY1] = static_cast<unsigned char>((pixels[chY1]-min)*iscale>>8);
    pixels+=4;
  }
}
