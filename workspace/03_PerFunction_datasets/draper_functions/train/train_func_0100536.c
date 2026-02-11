_BlockOffsetToPos(fl_BlockLayout * block, PT_DocPosition offset) const
{
	UT_return_val_if_fail(block, 0);
	return block->getPosition(false) + offset;
}
