mj_raster_cmd(int c_id, int in_size, byte* in, byte* buf2,
              gx_device_printer* pdev, gp_file* prn_stream)
{
  int band_size = 1;

  byte *out = buf2;

  int width = in_size;
  int count;

  byte* in_end = in + in_size;

  static char colour_number[] = "\004\001\002\000";

  byte *inp = in;
  byte *outp = out;
  register byte *p, *q;


  gp_fputs("\033r",prn_stream);
  gp_fputc(colour_number[c_id], prn_stream);


  for( p = inp, q = inp + 1 ; q < in_end ; ) {

    if( *p != *q ) {
      p += 2;
      q += 2;
    } else {


      if( p > inp && *p == *(p-1) )
           p--;


      for( q++ ; q < in_end && *q == *p ; q++ ) {
        if( (q-p) >= 128 ) {
          if( p > inp ) {
            count = p - inp;
            while( count > 128 ) {
              *outp++ = '\177';
              memcpy(outp, inp, 128);
              inp += 128;
              outp += 128;
              count -= 128;
            }
            *outp++ = (char) (count - 1);
            memcpy(outp, inp, count);
            outp += count;
          }
          *outp++ = '\201';
          *outp++ = *p;
          p += 128;
          inp = p;
        }
      }

      if( (q - p) > 2 ) {
        if( p > inp ) {
          count = p - inp;
          while( count > 128 ) {
            *outp++ = '\177';
            memcpy(outp, inp, 128);
            inp += 128;
            outp += 128;
            count -= 128;
          }
          *outp++ = (char) (count - 1);
          memcpy(outp, inp, count);
          outp += count;
        }
        count = q - p;
        *outp++ = (char) (256 - count + 1);
        *outp++ = *p;
        p += count;
        inp = p;
      } else
           p = q;
      if( q < in_end )
           q++;
    }
  }


  if( inp < in_end ) {

    count = in_end - inp;


    while( count > 128 ) {
      *outp++ = '\177';
      memcpy(outp, inp, 128);
      inp += 128;
      outp += 128;
      count -= 128;
    }

    *outp++ = (char) (count - 1);
    memcpy(outp, inp, count);
    outp += count;
  }


  gp_fwrite("\033.\001", 1, 3, prn_stream);

  if(pdev->y_pixels_per_inch == 720)
       gp_fputc('\005', prn_stream);
  else if(pdev->y_pixels_per_inch == 180)
       gp_fputc('\024', prn_stream);
  else
       gp_fputc('\012', prn_stream);

  if(pdev->x_pixels_per_inch == 720)
       gp_fputc('\005', prn_stream);
  else if(pdev->x_pixels_per_inch == 180)
       gp_fputc('\024', prn_stream);
  else
       gp_fputc('\012', prn_stream);

  gp_fputc(band_size, prn_stream);

  gp_fputc((width << 3) & 0xff, prn_stream);
  gp_fputc( width >> 5,	   prn_stream);

  gp_fwrite(out, 1, (outp - out), prn_stream);

  gp_fputc('\r', prn_stream);

  return 0;
}
