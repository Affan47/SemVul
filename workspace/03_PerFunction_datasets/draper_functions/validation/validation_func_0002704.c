pq_getbyte_if_available(unsigned char *c)
{
	int			r;

	if (PqRecvPointer < PqRecvLength)
	{
		*c = PqRecvBuffer[PqRecvPointer++];
		return 1;
	}


#ifdef WIN32
	pgwin32_noblock = 1;
#else
	if (!pg_set_noblock(MyProcPort->sock))
		ereport(ERROR,
				(errmsg("could not set socket to non-blocking mode: %m")));
#endif
	MyProcPort->noblock = true;
	PG_TRY();
	{
		r = secure_read(MyProcPort, c, 1);
		if (r < 0)
		{


			if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR)
				r = 0;
			else
			{


				ereport(COMMERROR,
						(errcode_for_socket_access(),
						 errmsg("could not receive data from client: %m")));
				r = EOF;
			}
		}
		else if (r == 0)
		{

			r = EOF;
		}
	}
	PG_CATCH();
	{


#ifdef WIN32
		pgwin32_noblock = 0;
#else
		if (!pg_set_block(MyProcPort->sock))
			ereport(FATAL,
					(errmsg("could not set socket to blocking mode: %m")));
#endif
		MyProcPort->noblock = false;
		PG_RE_THROW();
	}
	PG_END_TRY();
#ifdef WIN32
	pgwin32_noblock = 0;
#else
	if (!pg_set_block(MyProcPort->sock))
		ereport(FATAL,
				(errmsg("could not set socket to blocking mode: %m")));
#endif
	MyProcPort->noblock = false;

	return r;
}
