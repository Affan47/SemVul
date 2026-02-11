in(word_t addr)
{
  byte_t val = 0xff;

  switch (addr & 3)
    {
    case 0:
      val = in_A_DATA();
      break;
    case 1:
      val = in_A_CTRL();
      break;
    case 2:
      val = in_B_DATA();
      break;
    case 3:
      val = in_B_CTRL();
      break;
    }

  DBG(2, form("KCemu/PIO/6b/in",
              "PIO6_2::in():  addr = %04x, val = %02x\n",
              addr, val));

  return val;
}
