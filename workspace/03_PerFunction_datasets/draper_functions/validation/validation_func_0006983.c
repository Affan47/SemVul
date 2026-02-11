_resolve_shared_status(uint16_t user_flag, uint16_t part_max_share,
		       int cons_res_flag)
{

	if (part_max_share == 0)
		return 0;


	if ((part_max_share & SHARED_FORCE) &&
	    ((part_max_share & (~SHARED_FORCE)) > 1))
		return 2;

	if (cons_res_flag) {

		if (user_flag == 0)
			return 0;
		if (user_flag == 1)
			return 1;
		return 2;
	} else {

		if (part_max_share == 1)
			return 0;

		if (user_flag == 1)
			return 1;
	}
	return 0;
}
