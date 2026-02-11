processRGBAImage(imageStruct &image)
{
  unsigned char *pixels = image.data;
  int count = image.ysize * image.xsize;

     while (count--)    {
     int grey = (pixels[chRed  ] * RGB2GRAY_RED  +
                 pixels[chGreen] * RGB2GRAY_GREEN +
                 pixels[chBlue ] * RGB2GRAY_BLUE
                 ) >> 8;
     pixels[chRed] = pixels[chGreen] = pixels[chBlue] = (unsigned char)grey;
     pixels += 4;
     }
}
