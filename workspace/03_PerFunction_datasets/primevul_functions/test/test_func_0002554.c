closePGconn(PGconn *conn)
{


	sendTerminateConn(conn);


	conn->nonblocking = false;


	pqDropConnection(conn, true);
	conn->status = CONNECTION_BAD;
	conn->asyncStatus = PGASYNC_IDLE;
	conn->xactStatus = PQTRANS_IDLE;
	conn->pipelineStatus = PQ_PIPELINE_OFF;
	pqClearAsyncResult(conn);
	resetPQExpBuffer(&conn->errorMessage);
	release_conn_addrinfo(conn);


	pqDropServerData(conn);
}
