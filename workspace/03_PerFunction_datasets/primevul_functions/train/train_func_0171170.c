bool Item_subselect::set_fake_select_as_master_processor(void *arg)
{
  SELECT_LEX *fake_select= (SELECT_LEX*) arg;


  if (unit->outer_select()->master_unit()->fake_select_lex == fake_select)
  {


    fake_select->add_slave(unit);
    DBUG_ASSERT(unit->outer_select() == fake_select);

    for (SELECT_LEX *sl= unit->first_select(); sl; sl= sl->next_select())
      sl->context.outer_context= &(fake_select->context);


    unit->item= this;
    eliminated= FALSE;
  }
  return FALSE;
}
