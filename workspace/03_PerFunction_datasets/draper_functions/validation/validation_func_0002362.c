___device_tcp_client_select_raw_virt
   ___P((___device_stream *self,
         ___BOOL for_writing,
         int i,
         int pass,
         ___device_select_state *state),
        (self,
         for_writing,
         i,
         pass,
         state)
___device_stream *self;
___BOOL for_writing;
int i;
int pass;
___device_select_state *state;)
{
  ___device_tcp_client *d = ___CAST(___device_tcp_client*,self);
  int stage = (for_writing
               ? d->base.base.write_stage
               : d->base.base.read_stage);

  if (pass == ___SELECT_PASS_1)
    {
      if (stage != ___STAGE_OPEN)
        {
          state->timeout = ___time_mod.time_neg_infinity;
          return ___FIX(___SELECT_SETUP_DONE);
        }
      else
        {
#ifdef USE_POSIX

          if (d->try_connect_again != 0)
            {
              int interval = d->try_connect_interval_nsecs * 6 / 5;
              if (interval > 200000000)
                interval = 200000000;
              d->try_connect_interval_nsecs = interval;
              ___device_select_add_relative_timeout (state, i, interval * 1e-9);
            }
          else
            ___device_select_add_fd (state, d->s, for_writing);

          return ___FIX(___SELECT_SETUP_DONE);

#endif

#ifdef USE_WIN32

          d->io_events = 0;

          return ___FIX(___NO_ERR);

#endif
        }
    }

#ifdef USE_WIN32

  else if (pass == ___SELECT_PASS_2)
    {
      if (d->try_connect_again != 0)
        d->io_events = (FD_CONNECT | FD_CLOSE);
      else if (for_writing)
        d->io_events |= (FD_WRITE | FD_CLOSE);
      else
        d->io_events |= (FD_READ | FD_CLOSE);

      return ___FIX(___NO_ERR);
    }
  else if (pass == ___SELECT_PASS_3)
    {
      HANDLE wait_obj = d->io_event;

      ResetEvent (wait_obj);

      WSAEventSelect (d->s, wait_obj, d->io_events);

      ___device_select_add_wait_obj (state, i, wait_obj);

      return ___FIX(___SELECT_SETUP_DONE);
    }

#endif


  if (stage != ___STAGE_OPEN)
    state->devs[i] = NULL;
  else
    {
#ifdef USE_POSIX

      if (d->try_connect_again != 0 ||
          (for_writing
           ? FD_ISSET(d->s, &state->writefds)
           : FD_ISSET(d->s, &state->readfds)))
        {
          d->connect_done = 1;
          state->devs[i] = NULL;
        }

#endif

#ifdef USE_WIN32

      if (state->devs_next[i] != -1)
        {
          state->devs[i] = NULL;
          if (d->try_connect_again != 0)
            {
              d->connect_done = 1;
              d->try_connect_again = 2;
            }
        }

#endif
    }

  return ___FIX(___NO_ERR);
}
