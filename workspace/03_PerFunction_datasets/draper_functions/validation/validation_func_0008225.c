mailfolder_new(struct mailstorage * storage,
    const char * pathname, const char * virtual_name)
{
  struct mailfolder * folder;

  folder = malloc(sizeof(struct mailfolder));
  if (folder == NULL)
    goto err;

  if (pathname != NULL) {
    folder->fld_pathname = strdup(pathname);
    if (folder->fld_pathname == NULL)
      goto free;
  }
  else
    folder->fld_pathname = NULL;

  if (virtual_name != NULL) {
    folder->fld_virtual_name = strdup(virtual_name);
    if (folder->fld_virtual_name == NULL)
      goto free_pathname;
  }
  else
    folder->fld_virtual_name = NULL;

  folder->fld_storage = storage;

  folder->fld_session = NULL;
  folder->fld_shared_session = 0;
  folder->fld_pos = NULL;

  folder->fld_parent = NULL;
  folder->fld_sibling_index = 0;
  folder->fld_children = carray_new(128);
  if (folder->fld_children == NULL)
    goto free_virtualname;

  return folder;

free_virtualname:
  if (folder->fld_virtual_name != NULL)
    free(folder->fld_virtual_name);
free_pathname:
  if (folder->fld_pathname != NULL)
    free(folder->fld_pathname);
free:
  free(folder);
err:
  return NULL;
}
