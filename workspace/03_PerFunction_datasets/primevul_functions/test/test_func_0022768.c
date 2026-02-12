void st_select_lex_node::add_slave(st_select_lex_node *slave_arg)
{
  for (; slave; slave= slave->next)
    if (slave == slave_arg)
      return;

  if (slave)
  {
    st_select_lex_node *slave_arg_slave= slave_arg->slave;

    slave_arg->include_neighbour(slave);

    slave_arg->slave= slave_arg_slave;

    DBUG_ASSERT(slave_arg->master == this);
  }
  else
  {
    slave= slave_arg;
    slave_arg->master= this;
  }
}
