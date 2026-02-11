osst_flush_buffer(struct osst_tape * STp, struct osst_request ** aSRpnt, int seek_next)
{
	struct st_partstat * STps;
	int    backspace = 0, result = 0;
#if DEBUG
	char * name = tape_name(STp);
#endif


	if( STp->pos_unknown)
		return (-EIO);

	if (STp->ready != ST_READY)
		return 0;

	STps = &(STp->ps[STp->partition]);
	if (STps->rw == ST_WRITING || STp->dirty) {
		STp->write_type = OS_WRITE_DATA;
		return osst_flush_write_buffer(STp, aSRpnt);
	}
	if (STp->block_size == 0)
		return 0;

#if DEBUG
	printk(OSST_DEB_MSG "%s:D: Reached flush (read) buffer\n", name);
#endif

	if (!STp->can_bsr) {
		backspace = ((STp->buffer)->buffer_bytes + (STp->buffer)->read_pointer) / STp->block_size -
			    ((STp->buffer)->read_pointer + STp->block_size - 1        ) / STp->block_size ;
		(STp->buffer)->buffer_bytes = 0;
		(STp->buffer)->read_pointer = 0;
		STp->frame_in_buffer = 0;
	}

	if (!seek_next) {
		if (STps->eof == ST_FM_HIT) {
			result = cross_eof(STp, aSRpnt, 0);
			if (!result)
				STps->eof = ST_NOEOF;
			else {
				if (STps->drv_file >= 0)
					STps->drv_file++;
				STps->drv_block = 0;
			}
		}
		if (!result && backspace > 0)
			result = osst_seek_logical_blk(STp, aSRpnt, STp->logical_blk_num - backspace);
	}
	else if (STps->eof == ST_FM_HIT) {
		if (STps->drv_file >= 0)
			STps->drv_file++;
		STps->drv_block = 0;
		STps->eof = ST_NOEOF;
	}

	return result;
}
