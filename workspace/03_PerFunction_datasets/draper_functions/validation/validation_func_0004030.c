vtkWPString_PushChar(
  struct vtkWPString *str, char c)
{
  if (str->len + 2 > str->maxlen)
    {
    str->maxlen = (str->len + 2 + 2*str->maxlen);
    str->str = (char *)realloc(str->str, str->maxlen);
    }

  str->str[str->len++] = c;
  str->str[str->len] = '\0';
}
