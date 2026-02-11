test_remove_member (void)
{
  JsonObject *object = json_object_new ();
  JsonNode *node = json_node_new (JSON_NODE_NULL);

  json_object_set_member (object, "Null", node);

  json_object_remove_member (object, "Null");
  g_assert_cmpint (json_object_get_size (object), ==, 0);

  json_object_unref (object);
}
