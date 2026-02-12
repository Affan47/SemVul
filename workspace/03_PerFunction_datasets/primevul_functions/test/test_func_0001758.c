check_sudo (GError **error)
{
  const char *sudo_command_env = g_getenv ("SUDO_COMMAND");
  g_auto(GStrv) split_command = NULL;


  if (!sudo_command_env)
    return TRUE;


  split_command = g_strsplit (sudo_command_env, " ", 2);
  if (g_str_has_suffix (split_command[0], "flatpak"))
    return flatpak_fail_error (error, FLATPAK_ERROR, _("\"flatpak run\" is not intended to be run as `sudo flatpak run`, use `sudo -i` or `su -l` instead and invoke \"flatpak run\" from inside the new shell"));

  return TRUE;
}
