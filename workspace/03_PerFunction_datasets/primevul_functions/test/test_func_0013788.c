estack_push(etype_T type, char_u *name, long lnum)
{
    estack_T *entry;


    if (ga_grow(&exestack, 1) == OK)
    {
	entry = ((estack_T *)exestack.ga_data) + exestack.ga_len;
	entry->es_type = type;
	entry->es_name = name;
	entry->es_lnum = lnum;
#ifdef FEAT_EVAL
	entry->es_info.ufunc = NULL;
#endif
	++exestack.ga_len;
	return entry;
    }
    return NULL;
}
