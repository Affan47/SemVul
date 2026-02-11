mdread(SMgrRelation reln, BlockNumber blocknum, char *buffer)
{
	long		seekpos;
	int			nbytes;
	MdfdVec    *v;

	v = _mdfd_getseg(reln, blocknum, false, EXTENSION_FAIL);

#ifndef LET_OS_MANAGE_FILESIZE
	seekpos = (long) (BLCKSZ * (blocknum % ((BlockNumber) RELSEG_SIZE)));
	Assert(seekpos < BLCKSZ * RELSEG_SIZE);
#else
	seekpos = (long) (BLCKSZ * (blocknum));
#endif

	if (FileSeek(v->mdfd_vfd, seekpos, SEEK_SET) != seekpos)
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not seek to block %u of relation %u/%u/%u: %m",
						blocknum,
						reln->smgr_rnode.spcNode,
						reln->smgr_rnode.dbNode,
						reln->smgr_rnode.relNode)));

	if ((nbytes = FileRead(v->mdfd_vfd, buffer, BLCKSZ)) != BLCKSZ)
	{
		if (nbytes < 0)
			ereport(ERROR,
					(errcode_for_file_access(),
				   errmsg("could not read block %u of relation %u/%u/%u: %m",
						  blocknum,
						  reln->smgr_rnode.spcNode,
						  reln->smgr_rnode.dbNode,
						  reln->smgr_rnode.relNode)));


		if (zero_damaged_pages || InRecovery)
			MemSet(buffer, 0, BLCKSZ);
		else
			ereport(ERROR,
					(errcode(ERRCODE_DATA_CORRUPTED),
					 errmsg("could not read block %u of relation %u/%u/%u: read only %d of %d bytes",
							blocknum,
							reln->smgr_rnode.spcNode,
							reln->smgr_rnode.dbNode,
							reln->smgr_rnode.relNode,
							nbytes, BLCKSZ)));
	}
}
