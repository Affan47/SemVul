mkill_user_cb (USER * user, struct gkilldata *data)
{
    if (user->ip == data->ip)
    {
	if (data->sender && user->level >= data->sender->level &&
	    data->sender->level < LEVEL_ELITE)
	{
	    ASSERT (ISUSER (data->sender->con));
	    send_cmd (data->sender->con, MSG_SERVER_NOSUCH,
		      "kill failed: permission denied");
	    return;
	}
	kill_user_internal (data->sender->con, user, data->sender->nick,
			    data->sender, "%s", data->reason);
    }
}
