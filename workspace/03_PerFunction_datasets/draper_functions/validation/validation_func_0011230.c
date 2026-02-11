clear_channel(unsigned short *data, unsigned width, unsigned depth)
{
  int i;
  width *= depth;
  for (i = 0; i < width; i += depth)
    data[i] = 0;
}
