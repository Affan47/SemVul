__wcsnlen (s, maxlen)
     const wchar_t *s;
     size_t maxlen;
{
  size_t len = 0;

  while (maxlen > 0 && s[len] != L'\0')
    {
      ++len;
      if (--maxlen == 0 || s[len] == L'\0')
	return len;
      ++len;
      if (--maxlen == 0 || s[len] == L'\0')
	return len;
      ++len;
      if (--maxlen == 0 || s[len] == L'\0')
	return len;
      ++len;
      --maxlen;
    }

  return len;
}
