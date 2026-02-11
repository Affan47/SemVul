my_wc_mb_filename(CHARSET_INFO *cs __attribute__((unused)),
                  my_wc_t wc, uchar *s, uchar *e)
{
  int code;
  char hex[]= "0123456789abcdef";

  if (s >= e)
    return MY_CS_TOOSMALL;

  if (wc < 128 && filename_safe_char[wc])
  {
    *s= (uchar) wc;
    return 1;
  }

  if (s + 3 > e)
    return MY_CS_TOOSMALL3;

  *s++= MY_FILENAME_ESCAPE;
  if ((wc >= 0x00C0 && wc <= 0x05FF && (code= uni_0C00_05FF[wc - 0x00C0])) ||
      (wc >= 0x1E00 && wc <= 0x1FFF && (code= uni_1E00_1FFF[wc - 0x1E00])) ||
      (wc >= 0x2160 && wc <= 0x217F && (code= uni_2160_217F[wc - 0x2160])) ||
      (wc >= 0x24B0 && wc <= 0x24EF && (code= uni_24B0_24EF[wc - 0x24B0])) ||
      (wc >= 0xFF20 && wc <= 0xFF5F && (code= uni_FF20_FF5F[wc - 0xFF20])))
  {
    *s++= (code / 80) + 0x30;
    *s++= (code % 80) + 0x30;
    return 3;
  }


  if (s + 5 > e)
    return MY_CS_TOOSMALL5;

  *s++= hex[(wc >> 12) & 15];
  *s++= hex[(wc >> 8) & 15];
  *s++= hex[(wc >> 4) & 15];
  *s++= hex[(wc)      & 15];
  return 5;
}
