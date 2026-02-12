pqPacketSend(PGconn *conn, char pack_type,
			 const void *buf, size_t buf_len)
{

	if (pqPutMsgStart(pack_type, conn))
		return STATUS_ERROR;


	if (pqPutnchar(buf, buf_len, conn))
		return STATUS_ERROR;


	if (pqPutMsgEnd(conn))
		return STATUS_ERROR;


	if (pqFlush(conn))
		return STATUS_ERROR;

	return STATUS_OK;
}
