rpl_nanosleep (const struct timespec *requested_delay,
	       struct timespec *remaining_delay)
{


  struct timespec delay = *requested_delay;
  struct timespec t0;
  getnow (&t0);

  for (;;)
    {
      int r = nanosleep (&delay, remaining_delay);
      if (r == 0)
	{
	  time_t secs_sofar;
	  struct timespec now;
	  getnow (&now);

	  secs_sofar = now.tv_sec - t0.tv_sec;
	  if (requested_delay->tv_sec < secs_sofar)
	    return 0;
	  delay.tv_sec = requested_delay->tv_sec - secs_sofar;
	  delay.tv_nsec = requested_delay->tv_nsec - (now.tv_nsec - t0.tv_nsec);
	  if (delay.tv_nsec < 0)
	    {
	      if (delay.tv_sec == 0)
		return 0;
	      delay.tv_nsec += BILLION;
	      delay.tv_sec--;
	    }
	  else if (BILLION <= delay.tv_nsec)
	    {
	      delay.tv_nsec -= BILLION;
	      delay.tv_sec++;
	    }
	}
    }
}
