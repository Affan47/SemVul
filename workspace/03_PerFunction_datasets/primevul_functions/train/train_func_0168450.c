off_from_header (const char *p, size_t s)
{


  return from_header (p, s, "off_t",
		      0, TYPE_MAXIMUM (off_t),
		      false, false);
}
