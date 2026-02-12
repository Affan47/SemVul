pq_getbyte(void)
{
	Assert(PqCommReadingMsg);

	while (PqRecvPointer >= PqRecvLength)
	{
		if (pq_recvbuf())
			return EOF;
	}
	return (unsigned char) PqRecvBuffer[PqRecvPointer++];
}
