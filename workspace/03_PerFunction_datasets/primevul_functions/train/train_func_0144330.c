bjc_compress(const byte *row, uint raster, byte *compressed)
{
  const byte *end_row = row;
  register const byte *exam = row;
  register byte *cptr = compressed;

  end_row += raster;

  while ( exam < end_row ) {


    const byte *compr = exam;
    const byte *end_dis;
    const byte *next;
    register byte test, test2;

    test = *exam;
    while ( ++exam < end_row ) {
      test2 = *exam;
      if ( test == test2 )
          break;
      test = test2;
    }


    end_dis = exam - 1;
    if ( exam == end_row ) {
      next = --end_row;
    } else {

      next = exam + 1;
      while ( next < end_row && *next == test ) next++;
    }


    for ( ; ; ) {
      uint count = end_dis - compr;
      switch ( count ) {
      case 6: cptr[6] = compr[5];
      case 5: cptr[5] = compr[4];
      case 4: cptr[4] = compr[3];
      case 3: cptr[3] = compr[2];
      case 2: cptr[2] = compr[1];
      case 1: cptr[1] = compr[0];
        *cptr = count - 1;
        cptr += count + 1;
      case 0:
        break;
      default:
        if ( count > 128 ) count = 128;
        *cptr++ = count - 1;
        memcpy(cptr, compr, count);
        cptr += count, compr += count;
        continue;
      }
      break;
    }

    {

      int count = next - end_dis;
      if (next < end_row || test != 0)
        while ( count > 0 ) {

          int this = (count > 128 ? 128 : count);
          *cptr++ = 257 - this;
          *cptr++ = (byte)test;
          count -= this;
        }
      exam = next;
    }
  }
  return (uint)(cptr - compressed);
}
