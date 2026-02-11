gst_value_intersect_list (GValue * dest, const GValue * value1,
    const GValue * value2)
{
  guint i, size;
  GValue intersection = { 0, };
  gboolean ret = FALSE;

  size = VALUE_LIST_SIZE (value1);
  for (i = 0; i < size; i++) {
    const GValue *cur = VALUE_LIST_GET_VALUE (value1, i);


    if (!dest) {
      if (gst_value_intersect (NULL, cur, value2)) {
        ret = TRUE;
        break;
      }
      continue;
    }

    if (gst_value_intersect (&intersection, cur, value2)) {

      if (!ret) {
        gst_value_init_and_copy (dest, &intersection);
        ret = TRUE;
      } else if (GST_VALUE_HOLDS_LIST (dest)) {
        gst_value_list_append_value (dest, &intersection);
      } else {
        GValue temp = { 0, };

        gst_value_init_and_copy (&temp, dest);
        g_value_unset (dest);
        gst_value_list_merge (dest, &temp, &intersection);
        g_value_unset (&temp);
      }
      g_value_unset (&intersection);
    }
  }

  return ret;
}
