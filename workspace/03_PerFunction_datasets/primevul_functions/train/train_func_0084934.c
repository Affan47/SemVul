flatpak_filesystem_key_in_home (const char *filesystem)
{

  if (strcmp (filesystem, "home") == 0)
    return TRUE;


  if (g_strv_contains (flatpak_context_special_filesystems, filesystem) ||
      g_str_has_prefix (filesystem, "/"))
    return FALSE;


  if (g_str_has_prefix (filesystem, "xdg-run"))
    return FALSE;


  return TRUE;
}
