test_parse_tail() {
  char *s = "true false null [1, 2, 3] {}";
  json_ItemType types[] = { item_true, item_false, item_null, item_array, item_object };
  int i;
  for (i = 0; *s; ++i) {
    test_printf("i=%d *s=0x%02X (%c)\n", i, *s, *s);
    test_that(i < array_size(types));
    json_Item item;
    s = json_parse(s, &item);
    test_that(item.type == types[i]);
  }
  test_that(i == array_size(types));
  return test_success;
}
