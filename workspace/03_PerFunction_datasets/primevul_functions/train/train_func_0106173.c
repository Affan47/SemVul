static int still_interesting(struct commit_list *src, unsigned long date, int slop)
{


	if (!src)
		return 0;


	if (date < src->item->date)
		return SLOP;


	if (!everybody_uninteresting(src))
		return SLOP;


	return slop-1;
}
