GetCode(gif_source_ptr sinfo)


{
  register int accum;
  int offs, count;

  while (sinfo->cur_bit + sinfo->code_size > sinfo->last_bit) {


    if (sinfo->first_time) {
      sinfo->first_time = FALSE;
      return sinfo->clear_code;
    }
    if (sinfo->out_of_blocks) {
      WARNMS(sinfo->cinfo, JWRN_GIF_NOMOREDATA);
      return sinfo->end_code;
    }

    sinfo->code_buf[0] = sinfo->code_buf[sinfo->last_byte-2];
    sinfo->code_buf[1] = sinfo->code_buf[sinfo->last_byte-1];

    if ((count = GetDataBlock(sinfo, &sinfo->code_buf[2])) == 0) {
      sinfo->out_of_blocks = TRUE;
      WARNMS(sinfo->cinfo, JWRN_GIF_NOMOREDATA);
      return sinfo->end_code;
    }

    sinfo->cur_bit = (sinfo->cur_bit - sinfo->last_bit) + 16;
    sinfo->last_byte = 2 + count;
    sinfo->last_bit = sinfo->last_byte * 8;
  }


  offs = sinfo->cur_bit >> 3;
  accum = UCH(sinfo->code_buf[offs + 2]);
  accum <<= 8;
  accum |= UCH(sinfo->code_buf[offs + 1]);
  accum <<= 8;
  accum |= UCH(sinfo->code_buf[offs]);


  accum >>= (sinfo->cur_bit & 7);
  sinfo->cur_bit += sinfo->code_size;
  return accum & ((1 << sinfo->code_size) - 1);
}
