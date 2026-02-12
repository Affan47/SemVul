void handler::mark_trx_read_write_internal()
{
  Ha_trx_info *ha_info= &ha_thd()->ha_data[ht->slot].ha_info[0];


  if (ha_info->is_started())
  {
    DBUG_ASSERT(has_transaction_manager());


    if (table_share == NULL || table_share->tmp_table == NO_TMP_TABLE)
      ha_info->set_trx_read_write();
  }
}
