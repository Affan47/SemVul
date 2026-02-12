E_md4hash (uschar * passwd, uschar * p16)
{
int len;
int16x wpwd[129];


len = strlen (CS  passwd);
if (len > 128)
  len = 128;

_my_mbstowcs (wpwd, passwd, len);
wpwd[len] = 0;

len = _my_wcslen (wpwd) * sizeof (int16x);

mdfour (p16, US wpwd, len);
}
