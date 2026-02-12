start_initial_timeout(NCR_Instance inst)
{
  if (!inst->timer_running) {


    SRC_SetActive(inst->source);
  }

  restart_timeout(inst, INITIAL_DELAY);
}
