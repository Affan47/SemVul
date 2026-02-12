mirror_wait_for_free_in_flight_slot(MirrorBlockJob *s)
{

    mirror_wait_for_any_operation(s, false);
}
