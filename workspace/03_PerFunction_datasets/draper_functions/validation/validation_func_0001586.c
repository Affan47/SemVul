outputbyte(unsigned char c)
{
  if (binary)
    fwrite8(out, c);
  else
  {
    if (!covert)
    {
      if (!bytecount)
      {
        fprintf(out, "        dc.b ");
      }
      else fprintf(out, ",");
      fprintf(out, "$%02X", c);
      bytecount++;
      if (bytecount == 16)
      {
        bytecount = 0;
        fprintf(out, "\n");
      }
    }
    else
    {
      if (bytecount)
      {
        fprintf(out,",");
      }
      if (bytecount == 16)
      {
        fprintf(out,"\n");
        bytecount = 0;
      }
      bytecount++;
      fprintf(out, "0x%02x", c);
    }
  }
}
