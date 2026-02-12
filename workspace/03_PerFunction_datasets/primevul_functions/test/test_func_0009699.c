static void rtrs_clt_path_up(struct rtrs_clt_path *clt_path)
{
	struct rtrs_clt_sess *clt = clt_path->clt;
	int up;


	mutex_lock(&clt->paths_ev_mutex);
	up = ++clt->paths_up;


	if (up > MAX_PATHS_NUM && up == MAX_PATHS_NUM + clt->paths_num)
		clt->paths_up = clt->paths_num;
	else if (up == 1)
		clt->link_ev(clt->priv, RTRS_CLT_LINK_EV_RECONNECTED);
	mutex_unlock(&clt->paths_ev_mutex);


	clt_path->established = true;
	clt_path->reconnect_attempts = 0;
	clt_path->stats->reconnects.successful_cnt++;
}
