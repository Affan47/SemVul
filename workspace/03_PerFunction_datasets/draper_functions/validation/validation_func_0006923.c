HTTPRequest_Data1(hi, len)
HTTPInfo *hi;
ssize_t *len;
{
  char *line = NULL;
  const char *format = "Content-type: %s\r\nContent-length: %d\r\n";
  ChimeraRequest *wr = hi->wr;
  size_t linelen;

  if (wr->input_method == NULL ||
      strcasecmp(wr->input_method, "POST") != 0)
  {
    return(NULL);
  }

  if (wr->input_data != NULL && wr->input_len > 0 &&
      wr->input_type != NULL)
  {
    linelen = strlen(format) + strlen(wr->input_type) + 101;
    line = (char *)MPGet(hi->rmp, linelen);
    snprintf (line, linelen, format, wr->input_type, wr->input_len);
  }

  if (line != NULL) *len = strlen(line);

  return((byte *)line);
}
