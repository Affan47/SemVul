_wnck_get_frame_extents (Screen *screen,
                         Window  xwindow,
                         int    *left_frame,
                         int    *right_frame,
                         int    *top_frame,
                         int    *bottom_frame)
{
  gulong   *p_size;
  int       n_size;
  gboolean  retval;

  retval = FALSE;
  p_size = NULL;
  n_size = 0;

  _wnck_get_cardinal_list (screen, xwindow,
                           _wnck_atom_get ("_NET_FRAME_EXTENTS"),
                           &p_size, &n_size);

  if (p_size != NULL && n_size == 4)
    {
      *left_frame   = p_size[0];
      *right_frame  = p_size[1];
      *top_frame    = p_size[2];
      *bottom_frame = p_size[3];

      retval = TRUE;
    }

  if (p_size != NULL)
    g_free (p_size);

  return retval;
}
