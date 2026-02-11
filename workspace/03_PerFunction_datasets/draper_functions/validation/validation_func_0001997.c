vfss_dump(Vfs_handle *handle, char **errmsg)
{
  int i, st;
  Dsvec *names;

  names = NULL;
  st = vfs_list(handle, NULL, NULL, list_add, (void ***) &names);
  if (st == -1)
	return(-1);

  if (app_type == DACS_WEB_SERVICE)
	printf("\n");

  for (i = 0; i < dsvec_len(names); i++) {
	char *key, *value;
	size_t length;

	key = (char *) dsvec_ptr_index(names, i);
	if (vfs_get(handle, key, (void *) &value, &length) == -1)
	  return(-1);
	printf("%s%s%s\n", key, field_sep_char, value);
  }

  return(0);
}
