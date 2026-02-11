gst_value_collect_list_or_array (GValue * value, guint n_collect_values,
    GTypeCValue * collect_values, guint collect_flags)
{
  if (collect_flags & G_VALUE_NOCOPY_CONTENTS) {
    value->data[0].v_pointer = collect_values[0].v_pointer;
    value->data[1].v_uint = G_VALUE_NOCOPY_CONTENTS;
  } else {
    value->data[0].v_pointer =
        copy_garray_of_gstvalue ((GArray *) collect_values[0].v_pointer);
  }
  return NULL;
}
