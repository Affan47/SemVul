_rgb2gray (unsigned char *buffer, int pixels, int threshold)
{
#define WEIGHT_R 27
#define WEIGHT_G 54
#define WEIGHT_B 19
#define WEIGHT_W (WEIGHT_R + WEIGHT_G + WEIGHT_B)
  static int aWeight[BYTES_PER_PIXEL_COLOR] =
    { WEIGHT_R, WEIGHT_G, WEIGHT_B };
  int nbyte = pixels * BYTES_PER_PIXEL_COLOR;
  int acc = 0;
  int x;


  threshold = threshold;

  for (x = 0; x < nbyte; ++x)
    {
      acc += aWeight[x % BYTES_PER_PIXEL_COLOR] * buffer[x];
      if ((x + 1) % BYTES_PER_PIXEL_COLOR == 0)
        {
          buffer[x / BYTES_PER_PIXEL_COLOR] =
            (unsigned char) (acc / WEIGHT_W);
          acc = 0;
        }
    }
#undef WEIGHT_R
#undef WEIGHT_G
#undef WEIGHT_B
#undef WEIGHT_W
}
