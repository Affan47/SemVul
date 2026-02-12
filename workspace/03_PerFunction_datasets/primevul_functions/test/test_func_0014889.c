findtags_matchargs_init(findtags_match_args_T *margs, int flags)
{
    margs->matchoff = 0;
    margs->match_re = FALSE;
    margs->match_no_ic = FALSE;
    margs->has_re = (flags & TAG_REGEXP);
    margs->sortic = FALSE;
    margs->sort_error = FALSE;
}
