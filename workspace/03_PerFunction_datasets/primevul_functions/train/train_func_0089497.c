static int compare_info(const void *a_, const void *b_)
{
	struct pack_info *const *a = a_;
	struct pack_info *const *b = b_;

	if (0 <= (*a)->old_num && 0 <= (*b)->old_num)

		return (*a)->old_num - (*b)->old_num;
	else if (0 <= (*a)->old_num)

		return -1;
	else if (0 <= (*b)->old_num)

		return 1;


	if ((*a)->p == (*b)->p)
		return 0;
	else if ((*a)->p < (*b)->p)
		return -1;
	else
		return 1;
}
