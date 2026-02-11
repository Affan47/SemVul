spawn_enough_cpuworkers(void)
{
  int num_cpuworkers_needed = get_num_cpus(get_options());

  if (num_cpuworkers_needed < MIN_CPUWORKERS)
    num_cpuworkers_needed = MIN_CPUWORKERS;
  if (num_cpuworkers_needed > MAX_CPUWORKERS)
    num_cpuworkers_needed = MAX_CPUWORKERS;

  while (num_cpuworkers < num_cpuworkers_needed) {
    if (spawn_cpuworker() < 0) {
      log_warn(LD_GENERAL,"Cpuworker spawn failed. Will try again later.");
      return;
    }
    num_cpuworkers++;
  }
}
