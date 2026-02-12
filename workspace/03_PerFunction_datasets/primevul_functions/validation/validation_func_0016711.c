static void cil_reset_sens(struct cil_sens *sens)
{


	cil_list_destroy(&sens->cats_list, CIL_FALSE);
	sens->ordered = CIL_FALSE;
}
