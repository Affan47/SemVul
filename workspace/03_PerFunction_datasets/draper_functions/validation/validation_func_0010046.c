get_func (const char *name)
{
  func_t func = (func_t) dlsym (gnome_vfs_handle, name);
  if (func)
    return func;
  fprintf (stderr, "%s.\n", dlerror());
  return (func_t) 0;
}
