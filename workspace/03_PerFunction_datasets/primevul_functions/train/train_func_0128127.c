void write_ppm(libraw_processed_image_t *img, const char *basename)
{
  if (!img)
    return;

  if (img->type != LIBRAW_IMAGE_BITMAP)
    return;

  if (img->colors != 3)
    return;

  char fn[1024];
  snprintf(fn, 1024, "%s.ppm", basename);
  FILE *f = fopen(fn, "wb");
  if (!f)
    return;
  fprintf(f, "P6\n%d %d\n%d\n", img->width, img->height, (1 << img->bits) - 1);


#define SWAP(a, b)                                                             \
  {                                                                            \
    a ^= b;                                                                    \
    a ^= (b ^= a);                                                             \
  }
  if (img->bits == 16 && htons(0x55aa) != 0x55aa)
    for (unsigned i = 0; i < img->data_size; i += 2)
      SWAP(img->data[i], img->data[i + 1]);
#undef SWAP

  fwrite(img->data, img->data_size, 1, f);
  fclose(f);
}
