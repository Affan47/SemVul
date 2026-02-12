InitLZWCode(gif_source_ptr sinfo)

{

  sinfo->last_byte = 2;
  sinfo->code_buf[0] = 0;
  sinfo->code_buf[1] = 0;
  sinfo->last_bit = 0;
  sinfo->cur_bit = 0;
  sinfo->first_time = TRUE;
  sinfo->out_of_blocks = FALSE;


  sinfo->clear_code = 1 << sinfo->input_code_size;
  sinfo->end_code = sinfo->clear_code + 1;
  ReInitLZW(sinfo);
}
