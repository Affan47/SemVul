static inline bool is_valid_warning(int severity)
{

    if ((severity & ERR_MASK) != ERR_WARNING)
        return false;

    return WARN_IDX(severity) < ERR_WARN_ALL;
}
