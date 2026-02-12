sub_select_postjoin_aggr(JOIN *join, JOIN_TAB *join_tab, bool end_of_records)
{
  enum_nested_loop_state rc;
  AGGR_OP *aggr= join_tab->aggr;


  DBUG_ASSERT(aggr != NULL);

  DBUG_ENTER("sub_select_aggr_tab");

  if (join->thd->killed)
  {

    join->thd->send_kill_message();
    DBUG_RETURN(NESTED_LOOP_KILLED);
  }

  if (end_of_records)
  {
    rc= aggr->end_send();
    if (rc >= NESTED_LOOP_OK)
      rc= sub_select(join, join_tab, end_of_records);
    DBUG_RETURN(rc);
  }

  rc= aggr->put_record();

  DBUG_RETURN(rc);
}
