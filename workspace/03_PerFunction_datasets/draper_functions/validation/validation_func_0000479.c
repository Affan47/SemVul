udisks_daemon_util_setup_by_user (UDisksDaemon *daemon,
                                  UDisksObject *object,
                                  uid_t         user)
{
  gboolean ret;
  UDisksBlock *block = NULL;
  UDisksPartition *partition = NULL;
  UDisksState *state;
  uid_t setup_by_user;
  UDisksObject *crypto_object;

  ret = FALSE;

  state = udisks_daemon_get_state (daemon);
  block = udisks_object_get_block (object);
  if (block == NULL)
    goto out;
  partition = udisks_object_get_partition (object);


  if (udisks_state_has_loop (state, udisks_block_get_device (block), &setup_by_user))
    {
      if (setup_by_user == user)
        {
          ret = TRUE;
          goto out;
        }
    }


  if (partition != NULL)
    {
      UDisksObject *partition_object = NULL;
      partition_object = udisks_daemon_find_object (daemon, udisks_partition_get_table (partition));
      if (partition_object != NULL)
        {
          if (udisks_daemon_util_setup_by_user (daemon, partition_object, user))
            {
              ret = TRUE;
              g_object_unref (partition_object);
              goto out;
            }
          g_object_unref (partition_object);
        }
    }


  crypto_object = udisks_daemon_find_object (daemon, udisks_block_get_crypto_backing_device (block));
  if (crypto_object != NULL)
    {
      UDisksBlock *crypto_block;
      crypto_block = udisks_object_peek_block (crypto_object);
      if (udisks_state_find_unlocked_luks (state,
                                           udisks_block_get_device_number (crypto_block),
                                           &setup_by_user))
        {
          if (setup_by_user == user)
            {
              ret = TRUE;
              g_object_unref (crypto_object);
              goto out;
            }
        }
      g_object_unref (crypto_object);
    }


  if (g_strcmp0 (udisks_block_get_mdraid (block), "/") != 0)
    {
      uid_t started_by_user;
      if (udisks_state_has_mdraid (state, udisks_block_get_device_number (block), &started_by_user))
        {
          if (started_by_user == user)
            {
              ret = TRUE;
              goto out;
            }
        }
    }

 out:
  g_clear_object (&partition);
  g_clear_object (&block);
  return ret;
}
