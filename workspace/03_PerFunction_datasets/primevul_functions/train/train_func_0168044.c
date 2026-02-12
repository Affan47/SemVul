broadcast_timeout(void *arg)
{
  BroadcastDestination *destination;
  NTP_int64 orig_ts;
  struct timeval recv_ts;

  destination = ARR_GetElement(broadcasts, (long)arg);

  orig_ts.hi = 0;
  orig_ts.lo = 0;
  recv_ts.tv_sec = 0;
  recv_ts.tv_usec = 0;

  transmit_packet(MODE_BROADCAST, 6 ,
                  NTP_VERSION, 0, 0, &orig_ts, &recv_ts, NULL, NULL,
                  &destination->addr, &destination->local_addr);


  SCH_AddTimeoutInClass(destination->interval, SAMPLING_SEPARATION, SAMPLING_RANDOMNESS,
                        SCH_NtpBroadcastClass, broadcast_timeout, arg);
}
