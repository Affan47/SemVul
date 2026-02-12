ushort LibRaw::sget2Rev(uchar *s)

{
  if (order == 0x4d4d)

    return s[0] | s[1] << 8;
  else
    return s[0] << 8 | s[1];
}
