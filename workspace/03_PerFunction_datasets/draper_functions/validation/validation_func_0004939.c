set(const struct passwd *pwd_p) {
    if (pwd_p == NULL)
      return false;
    name = pwd_p->pw_name;
    uid = pwd_p->pw_uid;
    gid = pwd_p->pw_gid;
    home = GetEnv("HOME");

    if (home.empty() || uid != get_user_id()) home = pwd_p->pw_dir;
    return true;
  }
