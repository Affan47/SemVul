gamgi_mesa_select_press (int x, int y, gamgi_window *window)
{
int *box = gamgi->box;
int square = GAMGI_MESA_SELECT_SQUARE;

if (gamgi->state == GAMGI_MESA_SELECT_READY)
  {
  gamgi->window_mouse = window;
  gamgi->state = GAMGI_MESA_SELECT_SIZE;
  box[0] = box[2] = x;
  box[1] = box[3] = y;
  }

else if (gamgi->state == GAMGI_MESA_SELECT_DONE)
  {
  if (window != gamgi->window_mouse)
    {
    gamgi->state = GAMGI_MESA_SELECT_READY;
    gtk_widget_queue_draw (gamgi->window_mouse->area);
    gamgi_mesa_select_press (x, y, window);
    }

  else if ((x >= box[0] && x <= box[0] + square - 1) &&
  (y >= box[3] - square + 1 && y <= box[3]))
    {
    gamgi->state = GAMGI_MESA_SELECT_MOVE;
    }

  else if ((x >= box[2] - square + 1 && x <= box[2]) &&
  (y >= box[1] && y <= box[1] + square - 1))
    {
    gamgi->state = GAMGI_MESA_SELECT_RESIZE;
    }

  else
    {
    gamgi->state = GAMGI_MESA_SELECT_READY;
    gtk_widget_queue_draw (gamgi->window_mouse->area);
    gamgi_mesa_select_press (x, y, window);
    }
  }
}
