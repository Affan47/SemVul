execute()
{

  if( (cpu->simulation_mode == eSM_RUNNING) &&
      (simulation_start_cycle != get_cycles().get()) &&
      eval_Expression()) {

    invokeAction();

  } else
    m_replaced->execute();
}
