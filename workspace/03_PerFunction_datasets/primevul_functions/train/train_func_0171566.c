handler::ha_create_partitioning_metadata(const char *name,
                                         const char *old_name,
                                         int action_flag)
{


  DBUG_ASSERT(m_lock_type == F_UNLCK ||
              (!old_name && strcmp(name, table_share->path.str)));


  mark_trx_read_write();
  return create_partitioning_metadata(name, old_name, action_flag);
}
