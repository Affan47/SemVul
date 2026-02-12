inbound_identified (server *serv)
{
	if (serv->joindelay_tag)
	{

		fe_timeout_remove (serv->joindelay_tag);
		serv->joindelay_tag = 0;
		check_autojoin_channels (serv);
	}
}
