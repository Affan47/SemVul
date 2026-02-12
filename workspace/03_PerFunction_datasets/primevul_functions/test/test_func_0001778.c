flatpak_run_apply_env_prompt (FlatpakBwrap *bwrap, const char *app_id)
{


  flatpak_bwrap_set_env (bwrap, "FLATPAK_ID", app_id, TRUE);
  flatpak_bwrap_set_env (bwrap, "PS1", "[📦 $FLATPAK_ID \\W]\\$ ", FALSE);
}
