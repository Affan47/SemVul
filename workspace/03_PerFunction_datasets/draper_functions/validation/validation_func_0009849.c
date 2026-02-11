xlib_rgb_set_gray_cmap (Colormap cmap)
{
  int i;
  XColor color;
  int status;
  unsigned long pixels[256];
  int r, g, b, gray;

  for (i = 0; i < 256; i++)
    {
      color.pixel = i;
      color.red = i * 257;
      color.green = i * 257;
      color.blue = i * 257;
      status = XAllocColor(image_info->display, cmap, &color);
      pixels[i] = color.pixel;
#ifdef VERBOSE
      printf ("allocating pixel %d, %x %x %x, result %d\n",
	       color.pixel, color.red, color.green, color.blue, status);
#endif
    }


  colorcube = malloc(sizeof(unsigned char) * 4096);

  for (i = 0; i < 4096; i++)
    {
      r = (i >> 4) & 0xf0;
      r = r | r >> 4;
      g = i & 0xf0;
      g = g | g >> 4;
      b = (i << 4 & 0xf0);
      b = b | b >> 4;
      gray = (g + ((r + b) >> 1)) >> 1;
      colorcube[i] = pixels[gray];
    }
}
