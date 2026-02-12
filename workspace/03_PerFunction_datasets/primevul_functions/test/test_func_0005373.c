fuzzy_match_str_sort(fuzmatch_str_T *fm, int sz)
{

    qsort((void *)fm, (size_t)sz, sizeof(fuzmatch_str_T),
	    fuzzy_match_str_compare);
}
