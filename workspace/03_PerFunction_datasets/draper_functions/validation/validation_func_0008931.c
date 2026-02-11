anthy_gang_load_dic(xstr *sentence, int is_reverse)
{
  xstr *nx;
  if (!is_reverse && (nx = convert_vu(sentence))) {
    do_gang_load_dic(nx, is_reverse);
    anthy_free_xstr(nx);
  } else {
    do_gang_load_dic(sentence, is_reverse);
  }
}
