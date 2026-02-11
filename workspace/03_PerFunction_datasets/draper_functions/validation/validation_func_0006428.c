stpi_unpack_16_1(int length,
		 const unsigned char *in,
		 unsigned char **outs)
{
  unsigned char	tempin, bit;
  unsigned char temp[16];
  int j;

  if (length <= 0)
    return;

  memset(temp, 0, 16);

  for (bit = 128; length > 0; length--)
    {
      tempin = *in++;

      if (tempin & 128)
        temp[0] |= bit;
      if (tempin & 64)
        temp[1] |= bit;
      if (tempin & 32)
        temp[2] |= bit;
      if (tempin & 16)
        temp[3] |= bit;
      if (tempin & 8)
        temp[4] |= bit;
      if (tempin & 4)
        temp[5] |= bit;
      if (tempin & 2)
        temp[6] |= bit;
      if (tempin & 1)
        temp[7] |= bit;

      tempin = *in++;

      if (tempin & 128)
	temp[8] |= bit;
      if (tempin & 64)
	temp[9] |= bit;
      if (tempin & 32)
	temp[10] |= bit;
      if (tempin & 16)
	temp[11] |= bit;
      if (tempin & 8)
	temp[12] |= bit;
      if (tempin & 4)
	temp[13] |= bit;
      if (tempin & 2)
	temp[14] |= bit;
      if (tempin & 1)
	temp[15] |= bit;

      if (bit > 1)
        bit >>= 1;
      else
	{
	  bit     = 128;
	  for (j = 0; j < 16; j++)
	    *outs[j]++ = temp[j];

	  memset(temp, 0, 16);
	}
    }

  if (bit < 128)
    for (j = 0; j < 16; j++)
      *outs[j]++ = temp[j];
}
