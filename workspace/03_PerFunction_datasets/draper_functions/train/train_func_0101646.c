readit(struct testcase *test, struct tftphdr **dpp,
                  int convert )
{
  struct bf *b;

  bfs[current].counter = BF_FREE;
  current = !current;

  b = &bfs[current];
  if (b->counter == BF_FREE)
    read_ahead(test, convert);

  *dpp = &b->buf.hdr;
  return b->counter;
}
