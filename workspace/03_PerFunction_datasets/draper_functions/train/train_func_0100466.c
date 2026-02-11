dump(word_t addr)
{
  int a, b, c;
  for (a = 0;a < 8;a++)
    {
      cerr << hex << setw(4) << setfill('0') << (addr + 16 * a) << ": ";
      for (b = 0;b < 16;b++)
	{
	  cerr << hex << setw(2) << setfill('0') << memRead8(addr + 16 * a + b) << " ";
	  if (b == 7) cerr << ": ";
	}
      cerr << "   ";
      for (b = 0;b < 16;b++)
	{
	  c = memRead8(addr + 16 * a + b);
	  if (c > 0x20 && c < 0x80)
	    {
	      cerr << (char)c;
	    }
	  else
	    {
	      cerr << '.';
	    }
	}
      cerr << endl;
    }
}
