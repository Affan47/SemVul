mime_encode_base64(unsigned char *str, unsigned int nbytes, char **encoded)
{
  unsigned int n, rem, rem_bits, val;
  const unsigned char *p;
  Ds ds;

  n = nbytes;
  p = str;
  ds_init(&ds);
  rem = 0;

  rem_bits = 0;
  while (n > 0) {
	switch (rem_bits) {
	case 0:
	  val = (*p & 0xfc) >> 2;
	  ds_appendc(&ds, conv_table[val]);
	  rem = *p & 0x03;
	  rem_bits = 2;
	  break;
	case 2:
	  val = (rem << 4) | (*p & 0xf0) >> 4;
	  ds_appendc(&ds, conv_table[val]);
	  rem = *p & 0x0f;
	  rem_bits = 4;
	  break;
	case 4:
	  val = (rem << 2) | (*p & 0xc0) >> 6;
	  ds_appendc(&ds, conv_table[val]);
	  val = *p & 0x3f;
	  ds_appendc(&ds, conv_table[val]);
	  rem_bits = 0;
	  break;
	}
	p++;
	n--;
  }

  if (rem_bits == 2) {
	val = rem << 4;
	ds_appendc(&ds, conv_table[val]);
	ds_appendc(&ds, '=');
	ds_appendc(&ds, '=');
  }
  else if (rem_bits == 4) {
	val = rem << 2;
	ds_appendc(&ds, conv_table[val]);
	ds_appendc(&ds, '=');
  }

  ds_appendc(&ds, '\0');

  *encoded = ds_buf(&ds);
  return(ds_len(&ds));
}
