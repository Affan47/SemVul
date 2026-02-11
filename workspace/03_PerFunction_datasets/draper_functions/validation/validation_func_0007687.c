item_compare2(s1, s2)
    const void	*s1;
    const void	*s2;
{
    int		res;
    typval_T	rettv;
    typval_T	argv[3];
    int		dummy;


    if (item_compare_func_err)
	return 0;


    copy_tv(&(*(listitem_T **)s1)->li_tv, &argv[0]);
    copy_tv(&(*(listitem_T **)s2)->li_tv, &argv[1]);

    rettv.v_type = VAR_UNKNOWN;
    res = call_func(item_compare_func, (int)STRLEN(item_compare_func),
				 &rettv, 2, argv, 0L, 0L, &dummy, TRUE, NULL);
    clear_tv(&argv[0]);
    clear_tv(&argv[1]);

    if (res == FAIL)
	res = ITEM_COMPARE_FAIL;
    else

	res = get_tv_number_chk(&rettv, &item_compare_func_err);
    if (item_compare_func_err)
	res = ITEM_COMPARE_FAIL;
    clear_tv(&rettv);
    return res;
}
