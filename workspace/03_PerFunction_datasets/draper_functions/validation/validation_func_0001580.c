ensure_autoclear (MountData *data)
{
  UDisksLoop *loop;
  loop = udisks_client_get_loop_for_block (gvfs_udisks2_volume_monitor_get_udisks_client (data->volume->monitor),
                                           data->volume->block);
  if (loop != NULL)
    {
      if (!udisks_loop_get_autoclear (loop) && udisks_loop_get_setup_by_uid (loop) == getuid ())
        {

          udisks_loop_call_set_autoclear (loop, TRUE,
                                          g_variant_new ("a{sv}", NULL),
                                          NULL, NULL, NULL);
        }
      g_object_unref (loop);
    }
}
