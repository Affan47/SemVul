check_diff_overflow(fixed v0, fixed v1)
{
    if (v0 < v1) {
        if (v1 - v0 < 0)
            return true;
    } else {
        if (v0 - v1 < 0)
            return true;
    }
    return false;
}
