ext2fs_mmp_write(ext2_filsys fs, blk64_t mmp_blk, void *buf)
{
	struct mmp_struct *mmp_s = buf;
	struct timeval tv;
	errcode_t retval = 0;

	gettimeofday(&tv, 0);
	mmp_s->mmp_time = tv.tv_sec;
	fs->mmp_last_written = tv.tv_sec;

	if (fs->super->s_mmp_block < fs->super->s_first_data_block ||
	    fs->super->s_mmp_block > ext2fs_blocks_count(fs->super))
		return EXT2_ET_MMP_BAD_BLOCK;

#ifdef WORDS_BIGENDIAN
	ext2fs_swap_mmp(mmp_s);
#endif


	retval = io_channel_write_blk64(fs->io, mmp_blk, -(int)sizeof(struct mmp_struct), buf);

#ifdef WORDS_BIGENDIAN
	ext2fs_swap_mmp(mmp_s);
#endif


	io_channel_flush(fs->io);
	return retval;
}
