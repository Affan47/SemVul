GNUNET_SPEEDUP_start_ (const struct GNUNET_CONFIGURATION_Handle *cfg)
{
  if (GNUNET_OK != GNUNET_CONFIGURATION_get_value_time (cfg, "testing", "SPEEDUP_INTERVAL", &interval))
    return GNUNET_SYSERR;
  if (GNUNET_OK != GNUNET_CONFIGURATION_get_value_time (cfg, "testing", "SPEEDUP_DELTA", &delta))
    return GNUNET_SYSERR;

  if ((0 == interval.rel_value) || (0 == delta.rel_value))
  {
    LOG (GNUNET_ERROR_TYPE_DEBUG,
	 "Speed up disabled\n");
    return GNUNET_OK;
  }
  LOG (GNUNET_ERROR_TYPE_DEBUG,
       "Speed up execution time %llu ms every %llu ms\n",
       delta.rel_value, interval.rel_value);
  speedup_task = GNUNET_SCHEDULER_add_now_with_lifeness (GNUNET_NO, &do_speedup, NULL);
  return GNUNET_OK;
}
