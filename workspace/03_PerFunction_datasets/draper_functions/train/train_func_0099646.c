hatsuda_wall_triangle_draw(tenm_object *my, int priority)
{
  int status = 0;
  tenm_color color;
  double size;


  if (my == NULL)
  {
    fprintf(stderr, "hatsuda_wall_triangle_draw: my is NULL\n");
    return 0;
  }

  if (priority != 0)
    return 0;


  color = tenm_map_color(95, 13, 68);
  size = my->count_d[2];

  if (my->count[0] == 0)
  {
    if (tenm_draw_line((int) (my->x - size), (int) (my->y - size),
                       (int) (my->x - size), (int) (my->y + size),
                       3, color))
      status = 1;
    if (tenm_draw_line((int) (my->x - size), (int) (my->y + size),
                       (int) (my->x + size), (int) (my->y + size),
                       3, color))
      status = 1;
    if (tenm_draw_line((int) (my->x + size), (int) (my->y + size),
                       (int) (my->x - size), (int) (my->y - size),
                       3, color))
      status = 1;
  }
  else
  {
    if (tenm_draw_line((int) (my->x + size), (int) (my->y - size),
                       (int) (my->x + size), (int) (my->y + size),
                       3, color))
      status = 1;
    if (tenm_draw_line((int) (my->x + size), (int) (my->y + size),
                       (int) (my->x - size), (int) (my->y + size),
                       3, color))
      status = 1;
    if (tenm_draw_line((int) (my->x - size), (int) (my->y + size),
                       (int) (my->x + size), (int) (my->y - size),
                       3, color))
      status = 1;
  }

  return status;
}
