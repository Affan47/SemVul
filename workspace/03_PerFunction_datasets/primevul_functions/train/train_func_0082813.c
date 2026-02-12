b64decode(const uschar *code, uschar **ptr)
{
int x, y;
uschar *result = store_get(3*(Ustrlen(code)/4) + 1);

*ptr = result;


while ((x = *code++) != 0)
  {
  if (isspace(x)) continue;


  if (x > 127 || (x = dec64table[x]) == 255) return -1;

  while (isspace(y = *code++)) ;

  if (y == 0 || (y = dec64table[y]) == 255)
    return -1;

  *result++ = (x << 2) | (y >> 4);


  while (isspace(x = *code++)) ;

  if (x == '=')
    {
    while (isspace(x = *code++)) ;

    if (x != '=') return -1;
    while (isspace(y = *code++)) ;
    if (y != 0) return -1;

    break;
    }
  else
    {
    if (x > 127 || (x = dec64table[x]) == 255) return -1;
    *result++ = (y << 4) | (x >> 2);


    while (isspace(y = *code++)) ;

    if (y == '=')
      {
      while (isspace(y = *code++)) ;
      if (y != 0) return -1;

      break;
      }
    else
      {
      if (y > 127 || (y = dec64table[y]) == 255) return -1;
      *result++ = (x << 6) | y;

      }
    }
  }

*result = 0;
return result - *ptr;
}
