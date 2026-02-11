static_object_gamgi_list (FILE *fp, int depth_parent,
int *depth_last, int *id, gamgi_bool *error)
{
gamgi_window *window;


for (window = gamgi->window_start; window != NULL; window = window->next)
  static_object_window (window, GAMGI_CAST_OBJECT window,
  fp, depth_parent, depth_last, id, error);
}
