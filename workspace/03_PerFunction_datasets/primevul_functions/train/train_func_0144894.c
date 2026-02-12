cgi_passwd(const char *prompt)
{
  (void)prompt;

  fprintf(stderr, "DEBUG: cgi_passwd(prompt=\"%s\") called!\n",
          prompt ? prompt : "(null)");


  puts("Status: 401\n");
  exit(0);


  return (NULL);
}
