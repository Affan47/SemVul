get_monitor_edges (int which_monitor_set, int which_strut_set)
{
  GList *ret;
  GSList *struts;
  GList *xins;

  xins = NULL;
  g_assert (which_monitor_set >=0 && which_monitor_set <= 3);
  switch (which_monitor_set)
    {
    case 0:
      xins = g_list_prepend (xins, new_meta_rect (  0,   0, 1600, 1200));
      break;
    case 1:
      xins = g_list_prepend (xins, new_meta_rect (  0,   0,  800, 1200));
      xins = g_list_prepend (xins, new_meta_rect (800,   0,  800, 1200));
      break;
    case 2:
      xins = g_list_prepend (xins, new_meta_rect (  0,   0, 1600,  600));
      xins = g_list_prepend (xins, new_meta_rect (  0, 600, 1600,  600));
      break;
    case 3:
      xins = g_list_prepend (xins, new_meta_rect (  0,   0, 1600,  600));
      xins = g_list_prepend (xins, new_meta_rect (  0, 600,  800,  600));
      xins = g_list_prepend (xins, new_meta_rect (800, 600,  800,  600));
      break;
    }

  ret = NULL;

  struts = get_strut_list (which_strut_set);
  ret = meta_rectangle_find_nonintersected_monitor_edges (xins, struts);

  free_strut_list (struts);
  meta_rectangle_free_list_and_elements (xins);

  return ret;
}
