get_user_homedir(const char *username)
{
  struct passwd *pw;
  tor_assert(username);

  if (!(pw = getpwnam(username))) {
    log_err(LD_CONFIG,"User \"%s\" not found.", username);
    return NULL;
  }
  return tor_strdup(pw->pw_dir);
}
