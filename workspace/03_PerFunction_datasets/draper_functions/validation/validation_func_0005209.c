draw_help (void)
{
  int x, y, i;

  for (i = 0; i < 2 * angle; i++)
    {
      x = x_begin + HELP_RADIUS * cos (angle_shift + (i * G_PI) / angle);
      y = y_begin + HELP_RADIUS * sin (angle_shift + (i * G_PI) / angle);
      gdk_draw_rectangle (pixmap, gc_help, TRUE,
			  U2S (x) - 1, U2S (y) - 1, 3, 3);
    }
}
