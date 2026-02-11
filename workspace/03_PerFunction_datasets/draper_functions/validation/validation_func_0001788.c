filter_compare_lists(struct slapi_filter *f1,
				struct slapi_filter *f2)
{
    int buf[20], *tally;
    struct slapi_filter *fx1, *fx2;
    int count1 = 0, count2 = 0, ret, i, j, ok;

    for (fx1 = f1->f_list; fx1; fx1 = fx1->f_next, count1++);
    for (fx2 = f2->f_list; fx2; fx2 = fx2->f_next, count2++);
    if (count1 != count2)
	return 1;
    ret = 1;
    if (count1 > 20)
	tally = (int *)slapi_ch_malloc(count1);
    else
	tally = buf;
    if (!tally)
	goto done;
    for (i = 0; i < count1; i++)
	tally[i] = 0;

    fx1 = f1->f_list;
    for (i = 0; i < count1; i++, fx1 = fx1->f_next) {
	fx2 = f2->f_list;
	ok = 0;
	for (j = 0; j < count1; j++, fx2 = fx2->f_next) {
	    if (!tally[j] && (slapi_filter_compare(fx1, fx2) == 0)) {
		tally[j] = ok = 1;
		break;
	    }
	}
	if (!ok)
	    goto done;
    }

    ret = 0;

done:
    if ((count1 > 20) && tally)
	slapi_ch_free((void **)&tally);
    return ret;
}
