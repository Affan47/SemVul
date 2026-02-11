phosphor_reshape (Display *dpy, Window window, void *closure,
                 unsigned int w, unsigned int h)
{
  p_state *state = (p_state *) closure;
  Bool changed_p = resize_grid (state);

  if (! changed_p) return;

  textclient_reshape (state->tc, w, h,
                      state->grid_width  - 1,
                      state->grid_height - 1);
}
