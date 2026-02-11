emit_compression_string (int i)
{
  i -= 1;
  obstack_1grow (mangle_obstack, 'S');
  if (i >= 0)
    {
      static const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
      unsigned HOST_WIDE_INT n;
      unsigned HOST_WIDE_INT m=1;

      for (n = i; n >= 36; n /= 36, m *=36);

      while (m > 0)
	{
	  int digit = i / m;
	  obstack_1grow (mangle_obstack, digits [digit]);
	  i -= digit * m;
	  m /= 36;
	}
    }
  obstack_1grow (mangle_obstack, '_');
}
