babl_extension_load (const char *path)
{
  Babl *babl = NULL;

  HLIB  dl_handle = NULL;

  BablExtensionInitFunc init = NULL;
  BablExtensionDestroyFunc destroy = NULL;

  dl_handle = dlopen (path, RTLD_NOW);
  if (!dl_handle)
    {
      babl_log ("dlopen() failed:\n\t%s", dlerror ());
      return load_failed (babl);
    }
  init = (BablExtensionInitFunc) dlsym (dl_handle, "init");
  if (!init)
    {
      babl_log ("\n\tint babl_extension_init() function not found in extension '%s'", path);
      dlclose (dl_handle);
      return load_failed (babl);
    }

  destroy = (BablExtensionDestroyFunc) dlsym (dl_handle, "destroy");
  babl    = extension_new (path,
                           dl_handle,
                           destroy);

  babl_set_extender (babl);
  if (init ())
    {
      babl_log ("babl_extension_init() in extension '%s' failed (return!=0)", path);
      dlclose (dl_handle);
      return load_failed (babl);
    }

  babl_db_insert (db, babl);
  if (babl == babl_db_exist_by_name (db, path))
    {
      babl_set_extender (NULL);
      return babl;
    }
  else
    {
      return load_failed (babl);
    }
}
