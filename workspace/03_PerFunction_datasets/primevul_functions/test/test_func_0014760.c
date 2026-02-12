static inline void deshufflePalette(Image *image,PixelInfo* oldColormap)
{
  const size_t
    pages=image->colors/32,
    blocks=4,
    colors=8;

  int
    page;

  size_t
    i=0;

  (void) memcpy(oldColormap,image->colormap,(size_t)image->colors*
    sizeof(*oldColormap));


  for (page=0; page < (ssize_t) pages; page++)
  {
    memcpy(&(image->colormap[i+1*colors]),&(oldColormap[i+2*colors]),colors*
      sizeof(PixelInfo));
    memcpy(&(image->colormap[i+2*colors]),&(oldColormap[i+1*colors]),colors*
      sizeof(PixelInfo));

    i+=blocks*colors;
  }
}
