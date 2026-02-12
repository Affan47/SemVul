clear_status_flags_on_sybil(routerstatus_t *rs)
{
  rs->is_authority = rs->is_exit = rs->is_stable = rs->is_fast =
    rs->is_flagged_running = rs->is_named = rs->is_valid =
    rs->is_hs_dir = rs->is_v2_dir = rs->is_possible_guard = 0;


}
