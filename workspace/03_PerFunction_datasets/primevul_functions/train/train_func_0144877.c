cgi_initialize_string(const char *data)
{
  int	done;
  char	*s,
	ch,
	name[255],
	value[65536];


  if (data == NULL)
    return (0);


  while (*data != '\0')
  {


    for (s = name; *data != '\0'; data ++)
      if (*data == '=')
        break;
      else if (*data >= ' ' && s < (name + sizeof(name) - 1))
        *s++ = *data;

    *s = '\0';
    if (*data == '=')
      data ++;
    else
      return (0);


    for (s = value, done = 0; !done && *data != '\0'; data ++)
      switch (*data)
      {
	case '&' :
            done = 1;
            break;

	case '+' :
            if (s < (value + sizeof(value) - 1))
              *s++ = ' ';
            break;

	case '%' :


            if (!isxdigit(data[1] & 255) || !isxdigit(data[2] & 255))
	      return (0);

            if (s < (value + sizeof(value) - 1))
	    {
              data ++;
              ch = *data - '0';
              if (ch > 9)
        	ch -= 7;
              *s = (char)(ch << 4);

              data ++;
              ch = *data - '0';
              if (ch > 9)
        	ch -= 7;
              *s++ |= ch;
            }
	    else
	      data += 2;
            break;

	default :
	    if (*data >= ' ' && s < (value + sizeof(value) - 1))
              *s++ = *data;
            break;
      }

    *s = '\0';


    if (s > value)
      s --;

    while (s >= value && isspace(*s & 255))
      *s-- = '\0';


    if ((s = strrchr(name, '-')) != NULL && isdigit(s[1] & 255))
    {
      *s++ = '\0';
      if (value[0])
        cgiSetArray(name, atoi(s) - 1, value);
    }
    else if (cgiGetVariable(name) != NULL)
      cgiSetArray(name, cgiGetSize(name), value);
    else
      cgiSetVariable(name, value);
  }

  return (1);
}
