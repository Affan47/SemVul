static int hufEncode
    (const long long *hcode,
     const unsigned short *in,
     const int ni,
     int rlc,
     char *out)
{
  char *outStart = out;
  long long c = 0;
  int lc = 0;
  int s = in[0];
  int cs = 0;


  for (int i = 1; i < ni; i++) {


    if (s == in[i] && cs < 255) {
      cs++;
    } else {
      sendCode(hcode[s], cs, hcode[rlc], c, lc, out);
      cs = 0;
    }

    s = in[i];
  }


  sendCode(hcode[s], cs, hcode[rlc], c, lc, out);

  if (lc) *out = (c << (8 - lc)) & 0xff;

  return (out - outStart) * 8 + lc;
}
