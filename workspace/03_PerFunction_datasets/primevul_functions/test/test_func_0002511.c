sendTerminateConn(PGconn *conn)
{


	if (conn->sock != PGINVALID_SOCKET && conn->status == CONNECTION_OK)
	{


		pqPutMsgStart('X', conn);
		pqPutMsgEnd(conn);
		(void) pqFlush(conn);
	}
}
