ffi_trampoline_table_free (ffi_trampoline_table *table)
{

  if (table->prev != NULL)
    table->prev->next = table->next;

  if (table->next != NULL)
    table->next->prev = table->prev;


  vm_deallocate (mach_task_self (), table->config_page, PAGE_MAX_SIZE * 2);


  free (table->free_list_pool);
  free (table);
}
