get_largest_size_for_line_in_opposing_orientation (EggWrapBox       *box,
                                                   GtkOrientation    orientation,
                                                   GList            *cursor,
                                                   gint              line_length,
                                                   GtkRequestedSize *item_sizes,
                                                   gint              extra_pixels,
                                                   gint             *min_item_size,
                                                   gint             *nat_item_size)
{
  GList  *list;
  gint    max_min_size = 0;
  gint    max_nat_size = 0;
  gint    i;

  for (list = cursor, i = 0; list && i < line_length; list = list->next)
    {
      EggWrapBoxChild *child = list->data;
      gint             child_min, child_nat, this_item_size;

      if (!gtk_widget_get_visible (child->widget))
        continue;


      this_item_size = item_sizes[i].minimum_size;
      if (extra_pixels > 0 && ORIENTATION_SPREADING (box) == EGG_WRAP_BOX_SPREAD_EXPAND)
        {
          this_item_size++;
          extra_pixels--;
        }

      if (orientation == GTK_ORIENTATION_HORIZONTAL)
        gtk_widget_get_preferred_height_for_width (child->widget,
                                                   this_item_size,
                                                   &child_min, &child_nat);
      else
        gtk_widget_get_preferred_width_for_height (child->widget,
                                                   this_item_size,
                                                   &child_min, &child_nat);

      max_min_size = MAX (max_min_size, child_min);
      max_nat_size = MAX (max_nat_size, child_nat);

      i++;
    }

  if (min_item_size)
    *min_item_size = max_min_size;

  if (nat_item_size)
    *nat_item_size = max_nat_size;


  return list;
}
