memory_reaction()
{
  int cycle_length;

  if ( hash_search(&cycle_length) ) {
    if ( cycle_length < 2 * ( m - 1 ) ) {
      increase_prohib_period();
      return;
    }
  }
  else hash_insert();
  if ( it - last_prohib_period_mod > B )
    decrease_prohib_period();
}
