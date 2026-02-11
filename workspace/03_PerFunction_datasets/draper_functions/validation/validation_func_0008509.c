RTC_TimeInit(void (*after_hook)(void *), void *anything)
{
  if (driver_initialised) {
    (driver.time_init)(after_hook, anything);
  } else {
    LOG(LOGS_ERR, LOGF_Rtc, "Can't initialise from real time clock, driver not loaded");
    (after_hook)(anything);
  }
}
