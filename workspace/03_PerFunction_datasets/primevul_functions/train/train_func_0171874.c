static QString currentUser(void)
{
  struct passwd *current = getpwuid(getuid());
  QString fullname(current->pw_gecos);
  if (fullname.find(',') != -1)

    fullname.resize(fullname.find(','));

  QString username(current->pw_name);

  return fullname + " (" + username + ")";
}
