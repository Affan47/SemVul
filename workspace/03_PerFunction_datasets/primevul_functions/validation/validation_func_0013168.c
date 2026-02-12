ansicstr (string, len, flags, sawc, rlen)
     char *string;
     int len, flags, *sawc, *rlen;
{
  int c, temp;
  char *ret, *r, *s;
  unsigned long v;

  if (string == 0 || *string == '\0')
    return ((char *)NULL);

#if defined (HANDLE_MULTIBYTE)
  ret = (char *)xmalloc (4*len + 1);
#else
  ret = (char *)xmalloc (2*len + 1);
#endif
  for (r = ret, s = string; s && *s; )
    {
      c = *s++;
      if (c != '\\' || *s == '\0')
	*r++ = c;
      else
	{
	  switch (c = *s++)
	    {
#if defined (__STDC__)
	    case 'a': c = '\a'; break;
	    case 'v': c = '\v'; break;
#else
	    case 'a': c = (int) 0x07; break;
	    case 'v': c = (int) 0x0B; break;
#endif
	    case 'b': c = '\b'; break;
	    case 'e': case 'E':
	      c = ESC; break;
	    case 'f': c = '\f'; break;
	    case 'n': c = '\n'; break;
	    case 'r': c = '\r'; break;
	    case 't': c = '\t'; break;
	    case '1': case '2': case '3':
	    case '4': case '5': case '6':
	    case '7':
#if 1
	      if (flags & 1)
		{
		  *r++ = '\\';
		  break;
		}

#endif
	    case '0':


	      temp = 2 + ((flags & 1) && (c == '0'));
	      for (c -= '0'; ISOCTAL (*s) && temp--; s++)
		c = (c * 8) + OCTVALUE (*s);
	      c &= 0xFF;
	      break;
	    case 'x':
	      if ((flags & 2) && *s == '{')
		{
		  flags |= 16;
		  s++;
		}

	      for (temp = 2, c = 0; ISXDIGIT ((unsigned char)*s) && temp--; s++)
		c = (c * 16) + HEXVALUE (*s);


	      if (flags & 16)
		{
		  for ( ; ISXDIGIT ((unsigned char)*s); s++)
		    c = (c * 16) + HEXVALUE (*s);
		  flags &= ~16;
		  if (*s == '}')
		    s++;
	        }

	      else if (temp == 2)
		{
		  *r++ = '\\';
		  c = 'x';
		}
	      c &= 0xFF;
	      break;
#if defined (HANDLE_MULTIBYTE)
	    case 'u':
	    case 'U':
	      temp = (c == 'u') ? 4 : 8;
	      for (v = 0; ISXDIGIT ((unsigned char)*s) && temp--; s++)
		v = (v * 16) + HEXVALUE (*s);
	      if (temp == ((c == 'u') ? 4 : 8))
		{
		  *r++ = '\\';
		  break;
		}
	      else if (v <= 0x7f)
		{
		  c = v;
		  break;
		}
	      else
		{
		  temp = u32cconv (v, r);
		  r += temp;
		  continue;
		}
#endif
	    case '\\':
	      break;
	    case '\'': case '"': case '?':
	      if (flags & 1)
		*r++ = '\\';
	      break;
	    case 'c':
	      if (sawc)
		{
		  *sawc = 1;
		  *r = '\0';
		  if (rlen)
		    *rlen = r - ret;
		  return ret;
		}
	      else if ((flags & 1) == 0 && *s == 0)
		;
	      else if ((flags & 1) == 0 && (c = *s))
		{
		  s++;
		  if ((flags & 2) && c == '\\' && c == *s)
		    s++;
		  c = TOCTRL(c);
		  break;
		}

	    default:
		if ((flags & 4) == 0)
		  *r++ = '\\';
		break;
	    }
	  if ((flags & 2) && (c == CTLESC || c == CTLNUL))
	    *r++ = CTLESC;
	  *r++ = c;
	}
    }
  *r = '\0';
  if (rlen)
    *rlen = r - ret;
  return ret;
}
