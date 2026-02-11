Add(const R2Image& image)
{
  int nbytes = rowsize * height;
  unsigned char *p1 = pixels;
  unsigned char *p2 = image.pixels;
  while (--nbytes) {
    int value = *p1;
    value += *(p2++);
    if (value > 255) value = 255;
    *(p1++) = value;
  }
}
