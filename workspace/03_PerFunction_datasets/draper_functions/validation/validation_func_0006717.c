in(word_t addr)
{
  byte_t a = addr & 0xff;
  byte_t val = inout[a];

  switch (a)
    {
    case 0x84:
    case 0x86:
      break;
    default:
      DBG(0, form("KCemu/internal_error",
		  "Ports4: called in() with undefined address %04xh\n",
		  addr));
      break;
    }

  DBG(2, form("KCemu/Ports/4/in",
	      "Ports4: in() addr = %04x (returning %02x)\n",
	      addr, val));

  return val;
}
