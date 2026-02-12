last_status(
    int		morewin)
{

    last_status_rec(topframe, (p_ls == 2
			  || (p_ls == 1 && (morewin || !ONE_WINDOW))));
}
