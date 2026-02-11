get_group(gid_t gid)
{
  char		*name;
  struct group	*gr;
  char		buf[16];


  if (DefaultGroup)
    return (DefaultGroup);


  if ((name = hash_search(Groups, gid)) != NULL)
    return (name);


  setgrent();

  if ((gr = getgrgid(gid)) != NULL)
    name = gr->gr_name;
  else
  {


    sprintf(buf, "%u", (unsigned)gid);
    name = buf;
  }


  return (hash_insert(Groups, gid, name));
}
