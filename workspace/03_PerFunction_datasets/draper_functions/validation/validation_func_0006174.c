lf_read_int(
  xbmState *xbm,
  byte *data,
  int len,
  int *returnval)
{
  byte *new_pos;
  long answer = strtol((char *)(data + xbm->pos), (char **)(&new_pos), 0);
  if(new_pos == data + xbm->pos) return true;
  xbm->pos = new_pos - data;
  *returnval = answer;
  return false;
}
