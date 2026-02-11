SlruPhysicalWritePage(SlruCtl ctl, int pageno, int slotno, SlruFlush fdata)
{
	SlruShared	shared = ctl->shared;
	int			segno = pageno / SLRU_PAGES_PER_SEGMENT;
	int			rpageno = pageno % SLRU_PAGES_PER_SEGMENT;
	int			offset = rpageno * BLCKSZ;
	char		path[MAXPGPATH];
	int			fd = -1;


	if (fdata)
	{
		int			i;

		for (i = 0; i < fdata->num_files; i++)
		{
			if (fdata->segno[i] == segno)
			{
				fd = fdata->fd[i];
				break;
			}
		}
	}

	if (fd < 0)
	{


		SlruFileName(ctl, path, segno);
		fd = BasicOpenFile(path, O_RDWR | O_CREAT | PG_BINARY,
						   S_IRUSR | S_IWUSR);
		if (fd < 0)
		{
			slru_errcause = SLRU_OPEN_FAILED;
			slru_errno = errno;
			return false;
		}

		if (fdata)
		{
			if (fdata->num_files < MAX_FLUSH_BUFFERS)
			{
				fdata->fd[fdata->num_files] = fd;
				fdata->segno[fdata->num_files] = segno;
				fdata->num_files++;
			}
			else
			{


				fdata = NULL;
			}
		}
	}

	if (lseek(fd, (off_t) offset, SEEK_SET) < 0)
	{
		slru_errcause = SLRU_SEEK_FAILED;
		slru_errno = errno;
		if (!fdata)
			close(fd);
		return false;
	}

	errno = 0;
	if (write(fd, shared->page_buffer[slotno], BLCKSZ) != BLCKSZ)
	{

		if (errno == 0)
			errno = ENOSPC;
		slru_errcause = SLRU_WRITE_FAILED;
		slru_errno = errno;
		if (!fdata)
			close(fd);
		return false;
	}


	if (!fdata)
	{
		if (ctl->do_fsync && pg_fsync(fd))
		{
			slru_errcause = SLRU_FSYNC_FAILED;
			slru_errno = errno;
			close(fd);
			return false;
		}

		if (close(fd))
		{
			slru_errcause = SLRU_CLOSE_FAILED;
			slru_errno = errno;
			return false;
		}
	}

	return true;
}
