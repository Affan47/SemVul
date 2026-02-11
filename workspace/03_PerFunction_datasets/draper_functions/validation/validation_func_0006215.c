help_line_len(const char *ptr)
{
    int help_cols = (COLS > 24) ? COLS - 1 : 24;


    ssize_t wrap_loc = break_line(ptr, help_cols, TRUE);
    size_t retval = (wrap_loc < 0) ? 0 : wrap_loc;
    size_t retval_save = retval;


    while (*(ptr + retval) != '\0' && *(ptr + retval) != '\n')
	retval += move_mbright(ptr + retval, 0);


    if (strnlenpt(ptr, retval) > help_cols + 1)
	retval = retval_save;

    return retval;
}
