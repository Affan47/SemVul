setval_internal_tilde (int comind, const char *com, const char *val)
{
  bool ret;
  int homelen;
  char *home;
  char **pstring;
  ret = setval_internal (comind, com, val);


  if (((commands[comind].action == cmd_file) ||
       (commands[comind].action == cmd_directory))
      && ret && (*val == '~' && ISSEP (val[1])))
    {
      pstring = commands[comind].place;
      home = home_dir ();
      if (home)
        {
          homelen = strlen (home);
          while (homelen && ISSEP (home[homelen - 1]))
                 home[--homelen] = '\0';


          for (++val; ISSEP (*val); val++)
            ;
          *pstring = concat_strings (home, "/", val, (char *)0);
        }
    }
  return ret;
}
