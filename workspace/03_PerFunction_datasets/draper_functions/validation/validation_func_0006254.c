free_table_share(TABLE_SHARE *share)
{
  DBUG_ENTER("free_table_share");
  DBUG_PRINT("enter", ("table: %s.%s", share->db.str, share->table_name.str));
  DBUG_ASSERT(share->ref_count == 0);

  if (share->m_flush_tickets.is_empty())
  {


    share->destroy();
  }
  else
  {
    Wait_for_flush_list::Iterator it(share->m_flush_tickets);
    Wait_for_flush *ticket;


    mysql_mutex_assert_owner(&LOCK_open);

    while ((ticket= it++))
      (void) ticket->get_ctx()->m_wait.set_status(MDL_wait::GRANTED);


  }
  DBUG_VOID_RETURN;
}
