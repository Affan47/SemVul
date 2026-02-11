file_fillToken (char *token, int tokenlen)
{
  if (tokenlen == 0)
    return 0;
  if (file_tokenpos >= tokenlen - 1)
  {
    token [tokenlen - 1] = 0;
    return 0;
  }
  token [file_tokenpos ++] = file_buffer [file_ptr];
  token [file_tokenpos] = 0;
  return 1;
}
