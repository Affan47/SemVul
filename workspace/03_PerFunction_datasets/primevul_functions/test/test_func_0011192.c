qf_jump_first(qf_info_T *qi, int_u save_qfid, int forceit)
{
    if (qf_restore_list(qi, save_qfid) == FAIL)
	return;


    if (!qf_list_empty(qf_get_curlist(qi)))
	qf_jump(qi, 0, 0, forceit);
}
