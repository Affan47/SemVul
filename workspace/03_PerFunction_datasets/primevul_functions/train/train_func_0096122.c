gimp_channel_real_border (GimpChannel            *channel,
                          gint                    radius_x,
                          gint                    radius_y,
                          GimpChannelBorderStyle  style,
                          gboolean                edge_lock,
                          gboolean                push_undo)
{
  gint x1, y1, x2, y2;

  if (radius_x == 0 && radius_y == 0)
    {


      gimp_channel_clear (channel,
                          GIMP_CHANNEL_GET_CLASS (channel)->border_desc,
                          push_undo);
      return;
    }
  else if (radius_x <= 0 || radius_y <= 0)
    {


      g_return_if_reached();
    }

  if (! gimp_item_bounds (GIMP_ITEM (channel), &x1, &y1, &x2, &y2))
    return;

  x2 += x1;
  y2 += y1;

  if (gimp_channel_is_empty (channel))
    return;

  if (x1 - radius_x < 0)
    x1 = 0;
  else
    x1 -= radius_x;

  if (x2 + radius_x > gimp_item_get_width (GIMP_ITEM (channel)))
    x2 = gimp_item_get_width (GIMP_ITEM (channel));
  else
    x2 += radius_x;

  if (y1 - radius_y < 0)
    y1 = 0;
  else
    y1 -= radius_y;

  if (y2 + radius_y > gimp_item_get_height (GIMP_ITEM (channel)))
    y2 = gimp_item_get_height (GIMP_ITEM (channel));
  else
    y2 += radius_y;

  if (push_undo)
    gimp_channel_push_undo (channel,
                            GIMP_CHANNEL_GET_CLASS (channel)->border_desc);

  gimp_gegl_apply_border (gimp_drawable_get_buffer (GIMP_DRAWABLE (channel)),
                          NULL, NULL,
                          gimp_drawable_get_buffer (GIMP_DRAWABLE (channel)),
                          GEGL_RECTANGLE (x1, y1, x2 - x1, y2 - y1),
                          radius_x, radius_y, style, edge_lock);

  gimp_drawable_update (GIMP_DRAWABLE (channel), 0, 0, -1, -1);
}
