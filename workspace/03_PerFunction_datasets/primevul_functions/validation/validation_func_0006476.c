set_thesaurusfunc_option(void)
{
    int	retval;

    if (*curbuf->b_p_tsrfu != NUL)
    {

	retval = option_set_callback_func(curbuf->b_p_tsrfu,
							&curbuf->b_tsrfu_cb);
    }
    else
    {

	retval = option_set_callback_func(p_tsrfu, &tsrfu_cb);
    }

    return retval;
}
