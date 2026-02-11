global_worklists_free(void)
{
  if (client.worklists) {
    global_worklists_iterate_all(pgwl) {
      global_worklist_destroy(pgwl);
    } global_worklists_iterate_all_end;
    global_worklist_list_destroy(client.worklists);
    client.worklists = NULL;
  }
}
