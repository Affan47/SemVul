maki_dcc_send_free (makiDCCSend* dcc)
{
	if (dcc->status & s_incoming)
	{
		guint i;

		for (i = 0; i < s_in_num; i++)
		{
			if (dcc->d.in.sources[i] != 0)
			{
				g_source_remove(dcc->d.in.sources[i]);
			}
		}
	}
	else
	{
		guint i;

		for (i = 0; i < s_out_num; i++)
		{
			if (dcc->d.out.sources[i] != 0)
			{
				g_source_remove(dcc->d.out.sources[i]);
			}
		}
	}

	maki_dcc_send_close(dcc);

	maki_server_remove_user(dcc->server, maki_user_nick(dcc->user));

	g_free(dcc->path);
	g_free(dcc);
}
