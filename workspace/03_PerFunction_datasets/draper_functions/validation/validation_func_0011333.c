analyze_access_trees (struct access *access)
{
  bool ret = false;

  while (access)
    {
      if (analyze_access_subtree (access, NULL, true))
	ret = true;
      access = access->next_grp;
    }

  return ret;
}
