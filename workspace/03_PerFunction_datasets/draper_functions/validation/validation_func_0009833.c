is_rp_window_for_given_screen (Window w, rp_screen *s)
{
  if (w != s->key_window &&
      w != s->bar_window &&
      w != s->input_window &&
      w != s->frame_window &&
      w != s->help_window)
    return 0;
  return 1;
}
