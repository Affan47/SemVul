on_audiooutput_device_added_cb (const Ekiga::AudioOutputDevice & device, bool isDesired,  GtkWidget *prefs_window)
{
  GmPreferencesWindow *pw = NULL;
  g_return_if_fail (prefs_window != NULL);
  pw = gm_pw_get_pw (prefs_window);
  gnome_prefs_string_option_menu_add (pw->audio_player, (device.GetString()).c_str(), isDesired ? TRUE : FALSE);
  gnome_prefs_string_option_menu_add (pw->sound_events_output, (device.GetString()).c_str(), isDesired ? TRUE : FALSE);
}
