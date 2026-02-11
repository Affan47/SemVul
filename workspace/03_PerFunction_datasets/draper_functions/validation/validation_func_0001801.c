CheckCopyStreamStop(PGconn *conn, XLogRecPtr blockpos, uint32 timeline,
					char *basedir, stream_stop_callback stream_stop,
					char *partial_suffix, XLogRecPtr *stoppos, bool mark_done)
{
	if (still_sending && stream_stop(blockpos, timeline, false))
	{
		if (!close_walfile(basedir, partial_suffix, blockpos, mark_done))
		{

			return false;
		}
		if (PQputCopyEnd(conn, NULL) <= 0 || PQflush(conn))
		{
			fprintf(stderr, _("%s: could not send copy-end packet: %s"),
					progname, PQerrorMessage(conn));
			return false;
		}
		still_sending = false;
	}

	return true;
}
