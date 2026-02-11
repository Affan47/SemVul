init(FILE *f, int width, int height, int , int )
{
  file = f;
  imgWidth = width;

  switch (format)
  {
    case PNMWriter::PBM:
      fprintf(file, "P4\n%d %d\n", width, height);
      rowSize = (width + 7) >> 3;
      break;
    case PNMWriter::PGM:
      fprintf(file, "P5\n%d %d\n255\n", width, height);
      rowSize = width;
      break;
    case PNMWriter::PPM:
      fprintf(file, "P6\n%d %d\n255\n", width, height);
      rowSize = width * 3;
      break;
  }

  return true;
}
