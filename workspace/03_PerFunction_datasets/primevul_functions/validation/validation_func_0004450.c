static bool is_suppressed_warning(int severity)
{

    if (is_valid_warning(severity) && !(severity & ERR_USAGE))
        return !(warning_state[WARN_IDX(severity)] & WARN_ST_ENABLED);
    else
        return false;
}
