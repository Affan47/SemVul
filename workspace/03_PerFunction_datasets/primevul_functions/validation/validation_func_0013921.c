LZWReadByte(gif_source_ptr sinfo)

{
  register int code;
  int incode;


  if (sinfo->sp > sinfo->symbol_stack)
    return (int)(*(--sinfo->sp));


  code = GetCode(sinfo);

  if (code == sinfo->clear_code) {


    ReInitLZW(sinfo);
    do {
      code = GetCode(sinfo);
    } while (code == sinfo->clear_code);
    if (code > sinfo->clear_code) {
      WARNMS(sinfo->cinfo, JWRN_GIF_BADDATA);
      code = 0;
    }

    sinfo->firstcode = sinfo->oldcode = code;
    return code;
  }

  if (code == sinfo->end_code) {

    if (!sinfo->out_of_blocks) {
      SkipDataBlocks(sinfo);
      sinfo->out_of_blocks = TRUE;
    }

    WARNMS(sinfo->cinfo, JWRN_GIF_ENDCODE);

    return 0;
  }


  incode = code;

  if (code >= sinfo->max_code) {

    if (code > sinfo->max_code) {
      WARNMS(sinfo->cinfo, JWRN_GIF_BADDATA);
      incode = 0;
    }

    *(sinfo->sp++) = (UINT8)sinfo->firstcode;
    code = sinfo->oldcode;
  }


  while (code >= sinfo->clear_code) {
    *(sinfo->sp++) = sinfo->symbol_tail[code];
    code = sinfo->symbol_head[code];
  }

  sinfo->firstcode = code;


  if ((code = sinfo->max_code) < LZW_TABLE_SIZE) {

    sinfo->symbol_head[code] = (UINT16)sinfo->oldcode;
    sinfo->symbol_tail[code] = (UINT8)sinfo->firstcode;
    sinfo->max_code++;

    if (sinfo->max_code >= sinfo->limit_code &&
        sinfo->code_size < MAX_LZW_BITS) {
      sinfo->code_size++;
      sinfo->limit_code <<= 1;
    }
  }

  sinfo->oldcode = incode;
  return sinfo->firstcode;
}
