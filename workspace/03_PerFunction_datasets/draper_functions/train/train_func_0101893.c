wordsplit_c_unquote_copy (char *dst, const char *src, size_t n)
{
  int i = 0;
  int c;

  while (i < n)
    {
      if (src[i] == '\\')
	{
	  ++i;
	  if (src[i] == 'x' || src[i] == 'X')
	    {
	      if (n - i < 2)
		{
		  *dst++ = '\\';
		  *dst++ = src[i++];
		}
	      else
		{
		  int off = xtonum (&c, src + i + 1,
				    16, 2);
		  if (off == 0)
		    {
		      *dst++ = '\\';
		      *dst++ = src[i++];
		    }
		  else
		    {
		      *dst++ = c;
		      i += off + 1;
		    }
		}
	    }
	  else if ((unsigned char) src[i] < 128 && ISDIGIT (src[i]))
	    {
	      if (n - i < 1)
		{
		  *dst++ = '\\';
		  *dst++ = src[i++];
		}
	      else
		{
		  int off = xtonum (&c, src + i, 8, 3);
		  if (off == 0)
		    {
		      *dst++ = '\\';
		      *dst++ = src[i++];
		    }
		  else
		    {
		      *dst++ = c;
		      i += off;
		    }
		}
	    }
	  else
	    *dst++ = wordsplit_c_unquote_char (src[i++]);
	}
      else
	*dst++ = src[i++];
    }
  *dst = 0;
}
