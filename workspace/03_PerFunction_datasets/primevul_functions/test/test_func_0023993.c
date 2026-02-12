void plugin_shutdown(void)
{
  uint i, count= plugin_array.elements;
  struct st_plugin_int **plugins, *plugin;
  struct st_plugin_dl **dl;
  DBUG_ENTER("plugin_shutdown");

  if (initialized)
  {
    mysql_mutex_lock(&LOCK_plugin);

    reap_needed= true;


    while (reap_needed && (count= plugin_array.elements))
    {
      reap_plugins();
      for (i= 0; i < count; i++)
      {
        plugin= *dynamic_element(&plugin_array, i, struct st_plugin_int **);
        if (plugin->state == PLUGIN_IS_READY)
        {
          plugin->state= PLUGIN_IS_DELETED;
          reap_needed= true;
        }
      }
      if (!reap_needed)
      {


        unlock_variables(NULL, &global_system_variables);
        unlock_variables(NULL, &max_system_variables);
      }
    }

    plugins= (struct st_plugin_int **) my_alloca(sizeof(void*) * (count+1));


    for (i= 0; i < count; i++)
    {
      plugins[i]= *dynamic_element(&plugin_array, i, struct st_plugin_int **);

      if (plugins[i]->state == PLUGIN_IS_DELETED)
        plugins[i]->state= PLUGIN_IS_DYING;
    }
    mysql_mutex_unlock(&LOCK_plugin);


    for (i= 0; i < count; i++)
      if (!(plugins[i]->state & (PLUGIN_IS_UNINITIALIZED | PLUGIN_IS_FREED |
                                 PLUGIN_IS_DISABLED)))
      {


        plugin_deinitialize(plugins[i], false);
      }


    mysql_mutex_lock(&LOCK_plugin);


    for (i= 0; i < count; i++)
    {
      if (plugins[i]->ref_count)
        sql_print_error("Plugin '%s' has ref_count=%d after shutdown.",
                        plugins[i]->name.str, plugins[i]->ref_count);
      if (plugins[i]->state & PLUGIN_IS_UNINITIALIZED ||
          plugins[i]->state & PLUGIN_IS_DISABLED)
        plugin_del(plugins[i]);
    }


    cleanup_variables(&global_system_variables);
    cleanup_variables(&max_system_variables);
    mysql_mutex_unlock(&LOCK_plugin);

    initialized= 0;
    mysql_mutex_destroy(&LOCK_plugin);

    my_afree(plugins);
  }


  for (i= 0; i < MYSQL_MAX_PLUGIN_TYPE_NUM; i++)
    my_hash_free(&plugin_hash[i]);
  delete_dynamic(&plugin_array);

  count= plugin_dl_array.elements;
  dl= (struct st_plugin_dl **)my_alloca(sizeof(void*) * count);
  for (i= 0; i < count; i++)
    dl[i]= *dynamic_element(&plugin_dl_array, i, struct st_plugin_dl **);
  for (i= 0; i < plugin_dl_array.elements; i++)
    free_plugin_mem(dl[i]);
  my_afree(dl);
  delete_dynamic(&plugin_dl_array);

  my_hash_free(&bookmark_hash);
  free_root(&plugin_mem_root, MYF(0));
  free_root(&plugin_vars_mem_root, MYF(0));

  global_variables_dynamic_size= 0;

  DBUG_VOID_RETURN;
}
