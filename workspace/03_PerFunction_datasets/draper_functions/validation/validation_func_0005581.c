WritePngStream(const ByteImage &im, FILE *file) {
  png_structp png_ptr =
      png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr)
    return 0;

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
    return 0;

  if (setjmp(png_jmpbuf(png_ptr)))
    return 0;

  png_init_io(png_ptr, file);

  if (setjmp(png_jmpbuf(png_ptr)))
    return 0;


  char colour;
  if (im.Depth() == 3)
    colour = PNG_COLOR_TYPE_RGB;
  else if (im.Depth() == 1)
    colour = PNG_COLOR_TYPE_GRAY;
  else
    return 0;

  png_set_IHDR(png_ptr, info_ptr, im.Width(), im.Height(),
      8, colour, PNG_INTERLACE_NONE,
      PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  png_write_info(png_ptr, info_ptr);

  if (setjmp(png_jmpbuf(png_ptr)))
    return 0;

  png_bytep *row_pointers =
      (png_bytep*) malloc(sizeof(png_bytep) *im.Depth()* im.Height());

  unsigned char *ptr = (unsigned char *)im.Data();
  int y;
  for (y = 0; y < im.Height(); ++y)
    row_pointers[y] = (png_byte*) ptr + info_ptr->rowbytes*y;

  png_write_image(png_ptr, row_pointers);

  if (setjmp(png_jmpbuf(png_ptr)))
    return 0;

  free(row_pointers);

  png_write_end(png_ptr, NULL);

  return 1;
}
