garcon_menu_monitor_app_dirs (GarconMenu *menu)
{
  GFile *dir;
  GList *app_dirs;
  GList *dirs = NULL;
  GList *lp;

  g_return_if_fail (GARCON_IS_MENU (menu));
  g_return_if_fail (menu->priv->parent == NULL);

  g_return_if_fail (GARCON_IS_MENU (menu));


  app_dirs = garcon_menu_get_app_dirs (menu, TRUE);


  for (lp = app_dirs; lp != NULL; lp = lp->next)
    {
      dir = _garcon_file_new_relative_to_file (lp->data, menu->priv->file);
      dirs = g_list_prepend (dirs, dir);
    }


  garcon_menu_monitor_files (menu, dirs, garcon_menu_app_dir_changed);


  _garcon_g_list_free_full (dirs, g_object_unref);


  g_list_free (app_dirs);
}
