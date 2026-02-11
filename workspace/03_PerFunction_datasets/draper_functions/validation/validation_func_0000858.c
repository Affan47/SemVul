rt_set_horizontal_resolution (unsigned char *regs, int resolution)
{
  int base_resolution = 300;

  if (regs[0x2d] & 0x20)
    base_resolution *= 2;
  if (regs[0xd3] & 0x08)
    base_resolution *= 2;
  regs[0x7a] = base_resolution / resolution;
  return 0;
}
