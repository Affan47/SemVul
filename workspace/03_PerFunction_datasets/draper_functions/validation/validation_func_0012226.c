loggedIn()
{
	struct stat stat_buf;

	if (fseek(msg, 0L, SEEK_SET) < 0 || fstat(fileno(msg), &stat_buf) < 0)
	{
		fail(strerror(errno));
		return;
	}

	tot_count=stat_buf.st_size;
	byte_count=0;
	response_func= &mail::nntp::PostTask::doPostStatus;
	myserver->socketWrite("POST\r\n");
}
