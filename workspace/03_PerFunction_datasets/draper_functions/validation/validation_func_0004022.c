ggd_tag_sort_by_line (GPtrArray  *tags,
                      gint        direction)
{
  g_return_if_fail (tags != NULL);
  g_return_if_fail (direction != 0);

  g_ptr_array_sort_with_data (tags, tag_cmp_by_line_ptr_array,
                              GINT_TO_POINTER (direction));
}
