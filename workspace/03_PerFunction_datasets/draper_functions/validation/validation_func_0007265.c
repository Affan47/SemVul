pick_command_by_priority_background(const gearman_job_priority_t &arg)
{
  if (arg == GEARMAN_JOB_PRIORITY_NORMAL)
  {
    return GEARMAN_COMMAND_SUBMIT_JOB_BG;
  }
  else if (arg == GEARMAN_JOB_PRIORITY_HIGH)
  {
    return GEARMAN_COMMAND_SUBMIT_JOB_HIGH_BG;
  }

  return GEARMAN_COMMAND_SUBMIT_JOB_LOW_BG;
}
