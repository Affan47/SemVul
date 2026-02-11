osst_write_eod(struct osst_tape * STp, struct osst_request ** aSRpnt)
{
	int	result;
#if DEBUG
	char  * name = tape_name(STp);
#endif

	if (STp->raw) return 0;

	STp->write_type = OS_WRITE_EOD;
	STp->eod_frame_ppos = STp->first_frame_position;
#if DEBUG
	printk(OSST_DEB_MSG "%s:D: Writing EOD at fppos %d (fseq %d, lblk %d)\n", name,
			STp->eod_frame_ppos, STp->frame_seq_number, STp->logical_blk_num);
#endif
	STp->dirty = 1;

	result  = osst_flush_write_buffer(STp, aSRpnt);
	result |= osst_flush_drive_buffer(STp, aSRpnt);
	STp->eod_frame_lfa = --(STp->frame_seq_number);
	return result;
}
