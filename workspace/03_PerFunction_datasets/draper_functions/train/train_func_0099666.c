dump(const unsigned char *payload, int len, int indent=0)
{
  int i, off = 0;
  while (off < len) {
    for (int k=0; k<indent; k++)
      fprintf(stream, " ");

    fprintf(stream, "%04X   ", off);
    for (i=0; i<16; i++) {
      if ((i+off) < len)
        fprintf(stream, "%02X ", payload[i+off]);
      else
        fprintf(stream, "   ");
    }

    fprintf(stream, "   ");

    for (i=0; i<16; i++) {
      if ((i+off) < len)
        fprintf(stream, "%c", isprint(payload[i+off]) ? payload[i+off] : '.');
    }

    off += 16;
    fprintf(stream, "\n");
  }
}
