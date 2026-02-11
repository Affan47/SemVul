importshift_cb (GtkWidget * widget, guint datum)
{
  switch (datum)
    {
    case 1:
      yoff -= SCREEN_Y_2;
      break;
    case 4:
      yoff += SCREEN_Y_2;
      break;
    case 2:
      xoff -= SCREEN_X_2;
      break;
    case 3:
      xoff += SCREEN_X_2;
      break;
    }
  iszoomed = FALSE;
  expose_cb (NULL, 0);
  expose_mini_cb (NULL, 0);

  return TRUE;
}
