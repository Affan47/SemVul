ipv6_nmtoa(int * binary, uschar * buffer)
{
int i, j, k;
uschar * c = buffer;
uschar * d = NULL;

for (i = 0; i < 4; i++)
  {
  j = binary[i];
  c += sprintf(CS c, "%x:%x:", (j >> 16) & 0xffff, j & 0xffff);
  }

for (c = buffer, k = -1, i = 0; i < 8; i++)
  {
  if (*c == '0')
    {
    uschar * s = c;
    j = i;
    while (c[2] == '0') i++, c += 2;
    if (i-j > k)
      {
      k = i-j;
      d = s;
      }
    }
  while (*++c != ':') ;
  c++;
  }

c[-1] = '\0';


if (k >= 0)
  {
  c = d + 2*(k+1);
  if (d == buffer) c--;
  *d++ = ':';
  while ((*d++ = *c++)) ;
  }
else
  d = c;

return d - buffer;
}
