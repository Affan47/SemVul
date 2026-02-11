do_round ( time_in, round_incr )
time_t time_in;
int round_incr;
{
  int t, n, r;

  if ( round_incr == 0 )
    return ( time_in );

  t = (int) time_in;
  r = t % round_incr;
  t -= r;
  if ( r > ( round_incr / 2 ) )
    t += round_incr;

  return ( (time_t) t );
}
