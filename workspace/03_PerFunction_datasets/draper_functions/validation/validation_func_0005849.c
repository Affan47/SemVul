QueueFVal( nd, fval, tau, delay )
  nptr    nd;
  int     fval;
  double  tau, delay;
  {
    register evptr  ev;
    register Ulong  delta;
    int             queued = 0;

    delta = cur_delta + (Ulong) ps2d( delay );
    if( delta == cur_delta )
	delta++;

    while( (ev = nd->events) != NULL and ev->ntime >= delta )
      {
	if( ev->ntime == delta and ev->eval == fval )
	    break;
	PuntEvent( nd, ev );
      }

    delta -= cur_delta;

    if( fval != ((ev == NULL) ? nd->npot : ev->eval) )
      {
	enqueue_event( nd, fval, (long) delta, (long) ps2d( tau ) );
	queued = 1;
      }

    if( (debug & DEBUG_EV) and IsWatched( nd ) )
	print_final( nd, queued, tau, delta );
  }
