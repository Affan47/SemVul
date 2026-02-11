change_state(tState new_state)
{
    if (next_state && next_state != new_state)
        DEBUGMSGTL(("process", "Ignore transition to %s\n", next_state->name));
    next_state = new_state;
}
