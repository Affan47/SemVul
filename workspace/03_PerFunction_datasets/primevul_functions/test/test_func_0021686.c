flx_decode_delta_flc (GstFlxDec * flxdec, guchar * data, guchar * dest)
{
  gulong count, lines, start_l, opcode;
  guchar *start_p;

  g_return_val_if_fail (flxdec != NULL, FALSE);
  g_return_val_if_fail (flxdec->delta_data != NULL, FALSE);


  memcpy (dest, flxdec->delta_data, flxdec->size);

  lines = (data[0] + (data[1] << 8));
  if (lines > flxdec->hdr.height) {
    GST_ERROR_OBJECT (flxdec, "Invalid FLC packet detected. too many lines.");
    return FALSE;
  }
  data += 2;

  start_p = dest;
  start_l = lines;

  while (lines) {
    dest = start_p + (flxdec->hdr.width * (start_l - lines));


    while ((opcode = (data[0] + (data[1] << 8))) & 0xc000) {
      data += 2;
      if ((opcode & 0xc000) == 0xc000) {

        gulong skip = (0x10000 - opcode);
        if (skip > flxdec->hdr.height) {
          GST_ERROR_OBJECT (flxdec, "Invalid FLC packet detected. "
              "skip line count too big.");
          return FALSE;
        }
        start_l += skip;
        dest += flxdec->hdr.width * skip;
      } else {

        dest += flxdec->hdr.width;
        *dest++ = (opcode & 0xff);
      }
    }
    data += 2;


    while (opcode--) {

      guchar skip = *data++;
      dest += skip;


      count = *data++;

      if (count > 0x7f) {

        count = 0x100 - count;

        if (skip + count > flxdec->hdr.width) {
          GST_ERROR_OBJECT (flxdec, "Invalid FLC packet detected. "
              "line too long.");
          return FALSE;
        }

        while (count--) {
          *dest++ = data[0];
          *dest++ = data[1];
        }
        data += 2;
      } else {
        if (skip + count > flxdec->hdr.width) {
          GST_ERROR_OBJECT (flxdec, "Invalid FLC packet detected. "
              "line too long.");
          return FALSE;
        }


        while (count--) {
          *dest++ = *data++;
          *dest++ = *data++;
        }
      }
    }
    lines--;
  }

  return TRUE;
}
