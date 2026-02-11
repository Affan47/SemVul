create_window (GstWaylandSink * sink, struct display *display, int width,
    int height)
{
  struct window *window;

  if (sink->window)
    return;

  g_mutex_lock (&sink->wayland_lock);

  window = malloc (sizeof *window);
  window->display = display;
  window->width = width;
  window->height = height;
  window->redraw_pending = FALSE;

  window->surface = wl_compositor_create_surface (display->compositor);

  window->shell_surface = wl_shell_get_shell_surface (display->shell,
      window->surface);

  g_return_if_fail (window->shell_surface);

  wl_shell_surface_add_listener (window->shell_surface,
      &shell_surface_listener, window);

  wl_shell_surface_set_toplevel (window->shell_surface);

  sink->window = window;

  g_mutex_unlock (&sink->wayland_lock);
}
