json_object_get_values (JsonObject *object)
{
  GList *values, *l;

  g_return_val_if_fail (object != NULL, NULL);

  values = NULL;
  for (l = object->members_ordered; l != NULL; l = l->next)
    values = g_list_prepend (values, g_hash_table_lookup (object->members, l->data));

  return values;
}
