connectDBComplete(PGconn *conn)
{
	PostgresPollingStatusType flag = PGRES_POLLING_WRITING;
	time_t		finish_time = ((time_t) -1);
	int			timeout = 0;
	int			last_whichhost = -2;
	struct addrinfo *last_addr_cur = NULL;

	if (conn == NULL || conn->status == CONNECTION_BAD)
		return 0;


	if (conn->connect_timeout != NULL)
	{
		if (!parse_int_param(conn->connect_timeout, &timeout, conn,
							 "connect_timeout"))
		{

			conn->status = CONNECTION_BAD;
			return 0;
		}

		if (timeout > 0)
		{


			if (timeout < 2)
				timeout = 2;
		}
		else
			timeout = 0;
	}

	for (;;)
	{
		int			ret = 0;


		if (flag != PGRES_POLLING_OK &&
			timeout > 0 &&
			(conn->whichhost != last_whichhost ||
			 conn->addr_cur != last_addr_cur))
		{
			finish_time = time(NULL) + timeout;
			last_whichhost = conn->whichhost;
			last_addr_cur = conn->addr_cur;
		}


		switch (flag)
		{
			case PGRES_POLLING_OK:
				return 1;

			case PGRES_POLLING_READING:
				ret = pqWaitTimed(1, 0, conn, finish_time);
				if (ret == -1)
				{

					conn->status = CONNECTION_BAD;
					return 0;
				}
				break;

			case PGRES_POLLING_WRITING:
				ret = pqWaitTimed(0, 1, conn, finish_time);
				if (ret == -1)
				{

					conn->status = CONNECTION_BAD;
					return 0;
				}
				break;

			default:

				conn->status = CONNECTION_BAD;
				return 0;
		}

		if (ret == 1)
		{


			conn->try_next_addr = true;
			conn->status = CONNECTION_NEEDED;
		}


		flag = PQconnectPoll(conn);
	}
}
