xscroll (register xwin_t * win, int flag)
{
  if (flag == -1)
    {
      wmove (win->x_win, 0, 0);
      win->x_line = 0;
      win->x_col = 0;
      return;
    }
  win->x_line = (win->x_line + 1) % win->x_nlines;
  win->x_col = 0;
  wmove (win->x_win, win->x_line, win->x_col);
  wclrtoeol (win->x_win);
  wmove (win->x_win, (win->x_line + 1) % win->x_nlines, win->x_col);
  wclrtoeol (win->x_win);
  wmove (win->x_win, win->x_line, win->x_col);
}
