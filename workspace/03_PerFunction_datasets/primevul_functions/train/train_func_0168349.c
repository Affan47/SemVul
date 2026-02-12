getIntAt (const void *data)
{
  uint32_t p;

  memcpy (&p, data, 4);
  return ntohl (p);
}
