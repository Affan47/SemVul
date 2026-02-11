xsettings_list_lookup (XSettingsList *list,
		       const char    *name)
{
  XSettingsList *iter;

  iter = list;
  while (iter)
    {
      if (strcmp (name, iter->setting->name) == 0)
	return iter->setting;

      iter = iter->next;
    }

  return NULL;
}
