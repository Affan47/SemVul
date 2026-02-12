ReInitLZW(gif_source_ptr sinfo)

{
  sinfo->code_size = sinfo->input_code_size + 1;
  sinfo->limit_code = sinfo->clear_code << 1;
  sinfo->max_code = sinfo->clear_code + 2;
  sinfo->sp = sinfo->symbol_stack;
}
