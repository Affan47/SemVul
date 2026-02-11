ladish_studio_jack_conf_clear(void)
{
  struct list_head * node_ptr;

  INIT_LIST_HEAD(&g_studio.jack_params);
  while (!list_empty(&g_studio.jack_conf))
  {
    node_ptr = g_studio.jack_conf.next;
    list_del(node_ptr);
    ladish_studio_jack_conf_container_destroy(list_entry(node_ptr, struct jack_conf_container, siblings));
  }

  g_studio.jack_conf_valid = false;
}
