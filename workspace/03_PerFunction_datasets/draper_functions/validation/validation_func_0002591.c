AddFastPropertyUsingMap(Map* new_map,
                                               String* name,
                                               Object* value) {
  int index = new_map->PropertyIndexFor(name);
  if (map()->unused_property_fields() == 0) {
    ASSERT(map()->unused_property_fields() == 0);
    int new_unused = new_map->unused_property_fields();
    Object* values;
    { MaybeObject* maybe_values =
          properties()->CopySize(properties()->length() + new_unused + 1);
      if (!maybe_values->ToObject(&values)) return maybe_values;
    }
    set_properties(FixedArray::cast(values));
  }
  set_map(new_map);
  return FastPropertyAtPut(index, value);
}
