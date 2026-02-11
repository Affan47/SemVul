mbcharlen_ujis(CHARSET_INFO *cs __attribute__((unused)),uint c)
{
  return (isujis(c)? 2: isujis_ss2(c)? 2: isujis_ss3(c)? 3: 1);
}
